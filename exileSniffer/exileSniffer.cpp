/*

This is the UI thread - try not to hang it

*/

#include "stdafx.h"
#include "exileSniffer.h"
#include "utilities.h"
#include "qtextedit.h"
#include "packetIDs.h"
#include <fstream>

exileSniffer::exileSniffer(QWidget *parent)
	: QMainWindow(parent)
{


	ui.setupUi(this);

	setup_settings_tab();
	setup_raw_stream_tab();
	setup_decoded_messages_tab();
	initFilters();

	init_loginPkt_Actioners();
	init_gamePkt_Actioners();

	start_threads();

	setup_decryption_tab();

	std::cout << "writing to log " << "N:\\code\\POEcode\\poeSRE\\clientX\\Debug\\latestconndump.txt" << std::endl;
	outfile = std::ofstream("N:\\code\\POEcode\\poeSRE\\clientX\\Debug\\latestconndump.txt",
		std::ofstream::out | std::ofstream::app | std::ofstream::binary);

	//TODO: logfile configuration
	if (!outfile.is_open())
		outfile = std::ofstream("latestconndump.txt",
			std::ofstream::out | std::ofstream::app | std::ofstream::binary);

	outfile << std::endl << std::endl << "New sniffing session" << std::endl << std::endl;
}



void exileSniffer::setLabelActive(QLabel *lab, bool state)
{
	if (state)
	{
		lab->setGraphicsEffect(Q_NULLPTR);
	}
	else
	{
		QGraphicsColorizeEffect *effect;
		effect = new QGraphicsColorizeEffect;
		effect->setColor(QColor(225, 225, 225, 255));

		lab->setGraphicsEffect(effect);
	}
}

void exileSniffer::save_settings()
{
	settings->setValue("LoggingEnabled", ui.logsEnabledCheck->isChecked());
	settings->setValue("LogDir", ui.logDirLine->text());

	settings->setValue("PipeEnabled", ui.pipeFeedEnableCheck->isChecked());
	settings->setValue("PipeName", ui.namedPipeChosenName->text());
}

void exileSniffer::setup_settings_tab()
{
	ui.settingsChoiceList->setItemSelected(ui.settingsChoiceList->item(0), true);
	ui.settingsStack->setCurrentIndex(0);

	doLogging = settings->value("LoggingEnabled", true).toBool();
	ui.logsEnabledCheck->setChecked(doLogging);

	QString logdirstring = settings->value("LogDir", "fff").toString();
	ui.logDirLine->setText(logdirstring);
	logDir = logdirstring;

	doPipe = settings->value("PipeEnabled", true).toBool();
	ui.pipeFeedEnableCheck->setChecked(doPipe);

	QString pipename = settings->value("PipeName", "fff2").toString();
	ui.namedPipeChosenName->setText(pipename);

	settings->sync();
}

void exileSniffer::setup_decryption_tab()
{
	ui.keyExStatusWidget->setTitle("Client Key Extraction");
	ui.keyExStatusWidget->setText("Waiting for game processes");

	ui.sniffStatusWidget->setTitle("Network Stream Sniffing");
	ui.sniffStatusWidget->setText("Waiting for game packets");

	ui.no_decrypt_label->setPixmap(QPixmap(":/icons/padlock-red-locked.png"));
	ui.yes_decrypt_label->setPixmap(QPixmap(":/icons/padlock-green.png"));

	setStateNotDecrypting();

}

void exileSniffer::setup_raw_stream_tab()
{
	rawFiltersFormUI.setupUi(&filterFormObj);
	filterFormObj.setUI(&rawFiltersFormUI);

	toggleRawLineWrap(ui.rawLinewrapCheck->isChecked());

	connect(ui.ptHexPane->verticalScrollBar(), SIGNAL(valueChanged(int)),
		ui.ptASCIIPane->verticalScrollBar(), SLOT(setValue(int)));
	connect(ui.ptASCIIPane->verticalScrollBar(), SIGNAL(valueChanged(int)),
		ui.ptHexPane->verticalScrollBar(), SLOT(setValue(int)));
	ui.ptHexPane->verticalScrollBar()->hide();
}

//full clear and reload of displayed packets
void exileSniffer::refreshFilters()
{
	if (decodedListEntries.empty()) return;

	ui.decodedListTable->setRowCount(0);

	decodedCount_Displayed_Filtered = make_pair(0, 0);

	refreshingFilters = true;
	for (auto it = decodedListEntries.begin(); it != decodedListEntries.end(); it++)
	{
		if (packet_passes_decoded_filter(it->second->messageID))
		{
			addDecodedListEntry(it->first, it->second, false);
		}
	}
	refreshingFilters = false;
	updateDecodedFilterLabel();
}

void exileSniffer::initFilters()
{
	filterFormObj.populateFiltersList();
	filterFormObj.populatePresetsList();

	connect(&filterFormObj, SIGNAL(applyFilters()), this, SLOT(refreshFilters()));
}

void exileSniffer::setup_decoded_messages_tab()
{
	ui.decodedListTable->horizontalScrollBar()->setFixedHeight(10);
	ui.decodedListTable->horizontalHeader()->resizeSection(DECODED_SECTION_TIME, 70);
	ui.decodedListTable->horizontalHeader()->resizeSection(DECODED_SECTION_SENDER, 95);
	ui.decodedListTable->horizontalHeader()->resizeSection(DECODED_SECTION_MSGID, 45);
	ui.decodedListTable->horizontalHeader()->setSectionResizeMode(DECODED_SECTION_SUMMARY, QHeaderView::Stretch);
	ui.decodedListTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

	connect(ui.decodedRawText->verticalScrollBar(), SIGNAL(valueChanged(int)),
		ui.decodedRawHex->verticalScrollBar(), SLOT(setValue(int)));
	connect(ui.decodedRawHex->verticalScrollBar(), SIGNAL(valueChanged(int)),
		ui.decodedRawText->verticalScrollBar(), SLOT(setValue(int)));
}

void exileSniffer::start_threads()
{
	//start the packet capture thread to grab streams
	packetSniffer = new packet_capture_thread(&uiMsgQueue, &gamePktQueue, &loginPktQueue);
	std::thread packetSnifferInstance(&packet_capture_thread::ThreadEntry, packetSniffer);
	packetSnifferInstance.detach();

	//start the keyscanner thread to grab keys from clients
	keyGrabber = new key_grabber_thread(&uiMsgQueue);
	std::thread keyGrabberInstance(&key_grabber_thread::ThreadEntry, keyGrabber);
	keyGrabberInstance.detach();


	//start a thread to process streams
	packetProcessor = new packet_processor(keyGrabber, &uiMsgQueue, &gamePktQueue, &loginPktQueue, ggpk);
	std::thread packetProcessorInstance(&packet_processor::ThreadEntry, packetProcessor);
	packetProcessorInstance.detach();

	//start a timer to pull updates into the UI
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(read_UI_Q()));
	timer->start(10);
}

void exileSniffer::read_UI_Q()
{
	clock_t startTicks = clock();
	while (!uiMsgQueue.empty())
	{
		UI_MESSAGE *msg = uiMsgQueue.waitItem();
		action_UI_Msg(msg);

		float secondsElapsed = ((float)clock() - startTicks) / CLOCKS_PER_SEC;
		if (secondsElapsed > 0.15) //todo: season to taste
			break;
	}
}

void exileSniffer::set_keyEx_scanning_count(int total, int scanning)
{
	active_total_ClientScanCount = make_pair(scanning, total);

	if (activeDecryption) return;

	if (total == 0)
	{
		ui.keyExStatusWidget->setState(statusWidgetState::eBad);
		ui.keyExStatusWidget->setText("No running game clients detected");
	}
	else
	{
		if (scanning != total)
		{
			stringstream msg;
			if (total == 0)
				msg << "No active clients found but ";
			else if (total == 1)
				msg << "1 active client found but ";
			else
				msg << total << " active clients found but ";

			msg << scanning << " being scanned";
			ui.keyExStatusWidget->setText(QString::fromStdString(msg.str()));

			if (scanning > 0)
				ui.keyExStatusWidget->setState(statusWidgetState::ePending);
			else
				ui.keyExStatusWidget->setState(statusWidgetState::eBad);
		}
		else
		{
			ui.keyExStatusWidget->setState(statusWidgetState::ePending);

			stringstream scanmsg;
			if (scanning == 1)
				scanmsg << "Scanning game client for keydata";
			else
				scanmsg << "Scanning " << scanning << " game clients for keydata";

			ui.keyExStatusWidget->setText(QString::fromStdString(scanmsg.str()));
		}
	}
}

void exileSniffer::setStateDecrypting(int streamID)
{
	activeDecryption = true;
	latestDecryptingStream = streamID;

	DWORD decryptingProcess = packetProcessor->getLatestDecryptProcess();

	UIaddLogMsg("UI State set to decrypting", decryptingProcess, &uiMsgQueue);

	STREAM_NETWORK_DATA *streamData = packetSniffer->get_stream_data(streamID);
	if (streamData)
	{
		std::stringstream streamWidgetMsg;
		streamWidgetMsg << "Decrypting connection to " << 
			streamData->serverIP << ":" << streamData->serverPort << std::endl;
		ui.sniffStatusWidget->setText(QString::fromStdString(streamWidgetMsg.str()));
		ui.sniffStatusWidget->setState(statusWidgetState::eGood);

		ui.keyExStatusWidget->setText("Decryting stream for game process ID "+
			QString::number(decryptingProcess));
		ui.keyExStatusWidget->setState(statusWidgetState::eGood);
	}
	else
	{
		ui.keyExStatusWidget->setState(statusWidgetState::eBad);
		ui.keyExStatusWidget->setText("Error: Decrypting unknown stream. Process "+QString::number(decryptingProcess));
		ui.sniffStatusWidget->setState(statusWidgetState::eBad);
		ui.sniffStatusWidget->setText("ERROR: Decrypting unknown stream. Voices from beyond?");
	}

	setLabelActive(ui.yes_decrypt_label, true);
	setLabelActive(ui.no_decrypt_label, false);
	packetProcessor->requestIters(true);
	keyGrabber->suspend_scanning(decryptingProcess);

	ui.decrypt_details_stack->setCurrentIndex(1);
	ui.processTabs->setCurrentIndex(1);
}

void exileSniffer::resumeScanningEvent()
{
	if (transitionStream)
	{
		streamStates[transitionStream] = eStreamEnded;
		if (!activeDecryption)
		{
			keyGrabber->resume_scanning();
		}
		transitionStream = -1;
	}
}

void exileSniffer::setStateNotDecrypting()
{
	activeDecryption = false;
	packetProcessor->requestIters(false);
	setLabelActive(ui.yes_decrypt_label, false);
	setLabelActive(ui.no_decrypt_label, true);

	ui.decryptionStatusText->setText("Not Decrypting");

	DWORD processID = packetProcessor->getLatestDecryptProcess();

	clientHexData * client = get_clientdata(processID);
	if (client)
		client->isLoggedIn = false;

	UIaddLogMsg("UI State set to non-decrypting", processID, &uiMsgQueue);

	ui.decrypt_details_stack->setCurrentIndex(0);

	set_keyEx_scanning_count(active_total_ClientScanCount.second, active_total_ClientScanCount.first);
	updateStreamStateWidget();
	ui.processTabs->setCurrentIndex(0);
}

void exileSniffer::stopDecrypting()
{
	if (!activeDecryption) return;

	setStateNotDecrypting();

	for (auto streamIt = streamStates.begin(); streamIt != streamStates.end(); streamIt++)
	{
		if (streamIt->second == eStreamDecrypting)
		{
			streamStates.erase(streamIt);
			ui.sniffStatusWidget->setState(statusWidgetState::ePending);
			ui.sniffStatusWidget->setText("Sniffing for new game streams");
			set_keyEx_scanning_count(active_total_ClientScanCount.second, active_total_ClientScanCount.first);
			break;
		}
	}
}

void exileSniffer::updateStreamStateWidget()
{
	if (activeDecryption)
		return;

	int active = 0;
	int failed = 0;

	for (auto it = streamStates.begin(); it != streamStates.end(); it++)
	{
		if (it->second == eStreamFailed) failed++;
		active++;
	}

	if (active == 0)
	{
		ui.sniffStatusWidget->setState(statusWidgetState::eBad);
		ui.sniffStatusWidget->setText("No streams being sniffed");
	}
	else
	{
		std::stringstream msg;
		int actualActive = active - failed;
		if (actualActive > 0)
		{
			msg << "Sniffing for logon packets";

			if (failed > 0)
				msg << " (" << failed << " abandoned)";

			ui.sniffStatusWidget->setState(statusWidgetState::ePending);
		}
		else
		{
			msg << "Abandoned decryption of " << failed << " stream";
			if (failed != 1)
				msg << "s";
			msg << ". Must start before logon.";

			ui.sniffStatusWidget->setState(statusWidgetState::eBad);
		}

		ui.sniffStatusWidget->setText(QString::fromStdString(msg.str()));
	}

}

void exileSniffer::action_ended_stream(int streamID)
{
	auto streamIt = streamStates.find(streamID);
	if (streamIt == streamStates.end()) return;

	if (streamIt->second == eStreamDecrypting && latestDecryptingStream == streamID)
		setStateNotDecrypting();

	streamStates.erase(streamIt);
}

void exileSniffer::handle_stream_event(UI_STREAMEVENT_MSG *streamNote)
{
	if (streamNote->state == eStreamLoggingIn && !activeDecryption)
	{
		ui.decryptionStatusText->setText("Syncing decryption - don't press Play");
	}

	if (streamNote->state == eStreamDecrypting)
	{

		if (transitionStream != -1)
		{
			streamStates[transitionStream] = eStreamEnded;
			transitionStream = -1;
		}
		setStateDecrypting(streamNote->streamID);
	}

	if (streamNote->state == eStreamState::eStreamEnded)
	{
		action_ended_stream(streamNote->streamID);
		keyGrabber->resume_scanning();
		streamStates[streamNote->streamID] = streamNote->state;
	}
	else
	{
		if (streamNote->state == eStreamState::eStreamTransitionGame)
		{
			if (streamNote->streamID == latestDecryptingStream)
			{
				transitionStream = streamNote->streamID;
				QTimer::singleShot(15000, this, SLOT(resumeScanningEvent()));
			}
		}
		if (streamNote->state == eStreamState::eStreamTransitionLogin)
		{
			transitionStream = streamNote->streamID;
			setStateNotDecrypting();
			resumeScanningEvent();
		}
		streamStates[streamNote->streamID] = streamNote->state;
	}

	updateStreamStateWidget();
}

void exileSniffer::action_UI_Msg(UI_MESSAGE *msg)
{
	bool deleteAfterUse = true;

	switch (msg->msgType)
	{

		case uiMsgType::eMetaLog:
		{
			UI_METALOG_MSG *metalogmsg = (UI_METALOG_MSG *)msg;
			add_metalog_update(metalogmsg->stringData, metalogmsg->pid);
			break;
		}

		case uiMsgType::eClientEvent:
		{
			handle_client_event((UI_CLIENTEVENT_MSG *)msg);
			break;
		}

		case uiMsgType::eStreamEvent:
		{
			handle_stream_event((UI_STREAMEVENT_MSG *)msg);
			break;
		}

		case uiMsgType::eSniffingStarted:
		{
			UI_SNIFF_NOTE *sniffnote = (UI_SNIFF_NOTE *)msg;
			ui.sniffStatusWidget->setState(statusWidgetState::ePending);
			ui.sniffStatusWidget->setText("Sniffing for new game streams on interface "+ sniffnote->iface);
			break;
		}

		case uiMsgType::eLoginNote:
		{
			UI_LOGIN_NOTE *lgn = (UI_LOGIN_NOTE *)msg;
			auto it = clients.find(lgn->pid);
			if (it != clients.end())
				it->second->isLoggedIn = true;
			break;
		}

		case uiMsgType::ePacketHex:
		{
			deleteAfterUse = false; //archived
			handle_raw_packet_data((UI_RAWHEX_PKT *)msg);
			break;
		}

		case uiMsgType::eDecodedPacket:
		{
			deleteAfterUse = false; //archived
			UIDecodedPkt &uiDecodedMsg = *((UIDecodedPkt *)msg);

			if(!uiDecodedMsg.decodeError())
				action_decoded_packet(uiDecodedMsg); 
			else
			{
				if (uiDecodedMsg.wasAbandoned())
					action_decoded_packet(uiDecodedMsg);
				else
					action_undecoded_packet(uiDecodedMsg);
			}
			break;
		}

		case uiMsgType::eKeyUpdate:
		{
			UI_KEY *keymsg = (UI_KEY *)msg;
			ui.keyHexText->clear();
			QString keys = byteVecToHex(keymsg->key);
			keys.insert(48, '\n');
			ui.keyHexText->appendPlainText(keys);
			break;
		}

		case uiMsgType::eIVUpdate:
		{
			UI_IV *ivmsg = (UI_IV *)msg;
			if(!ivmsg->sendIV.empty())
				ui.sendIVText->setText(byteVecToHex(ivmsg->sendIV));
			if (!ivmsg->recvIV.empty())
				ui.recvIVText->setText(byteVecToHex(ivmsg->recvIV));
			break;
		}

		case uiMsgType::eCryptIterUpdate:
		{
			UI_CRYPTITER *ivmsg = (UI_CRYPTITER *)msg;
			if (!ivmsg->sendIter.empty())
				ui.sendIterText->setText(byteVecToHex(ivmsg->sendIter));
			if (!ivmsg->recvIter.empty())
				ui.recvIterText->setText(byteVecToHex(ivmsg->recvIter));
			break;
		}
	}

	if(deleteAfterUse)
		delete msg;
}

void exileSniffer::add_metalog_update(QString msg, DWORD pid)
{
	std::stringstream ss;
	ss << "[" << timestamp();
	if (pid != 0)
		ss << " - PID:"<<std::dec << pid;
	ss << "]: " << msg.toStdString() << std::endl;

	ui.metaLog->appendPlainText(QString::fromStdString(ss.str()));
}

void exileSniffer::handle_client_event(UI_CLIENTEVENT_MSG *cliEvtMsg)
{
	bool isRunning = cliEvtMsg->running;
	DWORD processID = cliEvtMsg->pid;
	if (processID)
	{
		if (!isRunning && activeDecryption && processID == packetProcessor->getLatestDecryptProcess())
		{
			setStateNotDecrypting();
			streamStates[latestDecryptingStream] = eStreamEnded;
		}

		set_keyEx_scanning_count(cliEvtMsg->totalClients, cliEvtMsg->totalScanning);
	}

	auto it = clients.find(processID);
	if (isRunning)
	{
		if (it == clients.end())
		{
			clientHexData *client = new clientHexData(true, true, QDir::current());
			client->isLoggedIn = false;
			clients.emplace(make_pair(processID, client));
		}
		else
		{
			//logged out and logged back in again
			clientHexData *oldclient = it->second;
			oldclient->isLoggedIn = false;
		}
	}
	else
	{
		if (it != clients.end())
		{
			clientHexData *oldclient = it->second;
			oldclient->isLoggedIn = false;
		}
		else
		{
			QString warnmsg = "WARNING: A client we have never seen just vanished \
								from the list of clients we have seen. Everything \
								is probably on fire.";
			add_metalog_update(warnmsg, processID);
		}
	}
}


std::string serverString(streamType server, string IP)
{
	switch (server)
	{
	case streamType::eGame:
		return "Server[Game]";
	case streamType::eLogin:
		return "Server[Login]";
	case streamType::ePatch:
		return "Server[Patch]";
	default:
		return "Server[Unknown]";
	}
}

void exileSniffer::insertRawText(std::string hexdump, std::string asciidump)
{
	int oldScrollPos = ui.ptHexPane->verticalScrollBar()->sliderPosition();

	QTextCursor userCursor = ui.ptHexPane->textCursor();
	ui.ptHexPane->moveCursor(QTextCursor::MoveOperation::End);
	ui.ptHexPane->append(QString::fromStdString(hexdump));
	ui.ptHexPane->setTextCursor(userCursor);

	userCursor = ui.ptASCIIPane->textCursor();
	ui.ptASCIIPane->moveCursor(QTextCursor::MoveOperation::End);
	ui.ptASCIIPane->append(QString::fromStdString(asciidump));
	ui.ptASCIIPane->setTextCursor(userCursor);

	if(!ui.rawAutoScrollCheck->isChecked())
		ui.ptASCIIPane->verticalScrollBar()->setSliderPosition(oldScrollPos);
}

void exileSniffer::output_hex_to_file(UI_RAWHEX_PKT *pkt, std::ofstream& file)
{
	if (!file.is_open()) return;

	std::stringstream mixeddump;

	char timestamp[20];
	struct tm *tm = gmtime(&pkt->createdtime);
	strftime(timestamp, sizeof(timestamp), "%H:%M:%S", tm);

	mixeddump << "#" << rawCount_Recorded_Filtered.first << " " << timestamp << " ";

	if (pkt->incoming)
		mixeddump << serverString(pkt->stream, "f") << " to PlayerClient";
	else
		mixeddump << "PlayerClient to " << serverString(pkt->stream, "f");
	mixeddump << " (" << std::dec << pkt->pktBytes->size() << " bytes)" << std::endl;

	stringstream::pos_type bytesStart = mixeddump.tellp();

	mixeddump << std::setfill('0') << std::uppercase << "  ";
	for (int i = 0; i < pkt->pktBytes->size(); ++i)
	{
		byte item = pkt->pktBytes->at(i);

		if (item)
			mixeddump << " " << std::hex << std::setw(2) << (int)item;
		else
			mixeddump << " 00";

		if ((i + 1) % UIhexPacketsPerRow == 0)
		{
			mixeddump << std::endl << "  ";
		}
	}
	mixeddump << "\n" << std::endl << std::nouppercase;

	mixeddump << "   ";
	for (int i = 0; i < pkt->pktBytes->size(); ++i)
	{
		byte item = pkt->pktBytes->at(i);

		if (item >= ' ' && item <= '~')
			mixeddump << (char)item;
		else
			mixeddump << '.';//replace unprintable with dots

		if ((i + 1) % UIhexPacketsPerRow == 0)
		{
			mixeddump << std::endl << "   ";
		}
	}

	mixeddump << "\n" << std::endl;

	std::string hexdumpstring = mixeddump.str();

	file << hexdumpstring << std::endl;
}

//todo: bold first two bytes, may need to add a 'continuationpacket' field
void exileSniffer::output_hex_to_pane(UI_RAWHEX_PKT *pkt)
{
	std::stringstream hexdump;
	std::stringstream asciidump;

	char timestamp[20];
	struct tm *tm = gmtime(&pkt->createdtime);
	strftime(timestamp, sizeof(timestamp), "%H:%M:%S", tm);

	hexdump << "#" << rawCount_Recorded_Filtered.first << " " << timestamp << " ";

	if (pkt->incoming)
		hexdump << serverString(pkt->stream, "f") << " to PlayerClient";
	else
		hexdump << "PlayerClient to " << serverString(pkt->stream, "f");
	hexdump << "(" << std::dec << pkt->pktBytes->size() << " bytes)" << std::endl;
	asciidump << std::endl;


	stringstream::pos_type bytesStart = hexdump.tellp();

	hexdump << std::setfill('0') << std::uppercase << " ";
	for (int i = 0; i < pkt->pktBytes->size(); ++i)
	{
		byte item = pkt->pktBytes->at(i);

		if (item)
			hexdump << " " << std::hex << std::setw(2) << (int)item;
		else
			hexdump << " 00";

		if (item >= ' ' && item <= '~')
			asciidump << (char)item;
		else
			asciidump << '.';//replace unprintable with dots

		if ((i + 1) % UIhexPacketsPerRow == 0)
		{
			hexdump << std::endl << "  ";
			asciidump << std::endl;
		}
	}
	hexdump << "\n" << std::endl << std::nouppercase;
	asciidump << "\n" << std::endl;

	std::string hexdumpstring = hexdump.str();
	//todo: work out position from bytes*2 + bytes*space + bytes/bytesperline*space
	//if (pkt->decodeFailed)
	//	hexdumpstring.at()
	outfile << hexdumpstring << std::endl;
	insertRawText(hexdumpstring, asciidump.str());

}

bool exileSniffer::packet_passes_decoded_filter(ushort msgID)
{
	return (filterFormObj.isDisplayed(msgID));
}

clientHexData * exileSniffer::get_clientdata(DWORD pid)
{
	clientHexData *client = NULL;

	if (pid == 0) //logon packet - unknown process yet
	{
		//until we go down the effort path of associating ports with PIDs
		//we can assign logon packets to the first unauthenticated process
		auto it = clients.begin();
		for (; it != clients.end(); it++)
			if (!it->second->isLoggedIn)
			{
				client = it->second;
				break;
			}
	}
	else
	{
		auto it = clients.find(pid);
		if (it != clients.end())
		{
			client = it->second;
		}
	}

	return client;
}

void exileSniffer::handle_raw_packet_data(UI_RAWHEX_PKT *pkt)
{

	clientHexData *client = get_clientdata(pkt->pid);

	if (!client)
	{
		add_metalog_update("Warning: Dropped packet with no associated PID", pkt->pid);
		return;
	}

	if (packet_passes_decoded_filter(pkt->startBytes))
	{
		output_hex_to_pane(pkt);
		output_hex_to_file(pkt, client->get_filtered_hexlog());
	}
	else
		++rawCount_Recorded_Filtered.second;
	++rawCount_Recorded_Filtered.first;

	output_hex_to_file(pkt, client->get_unfiltered_hexlog());

	client->rawHexPackets.push_back(pkt);
	updateRawFilterLabel();
}


void exileSniffer::rawBytesRowChanged(QString arg)
{
	//check the entry is all digits
	QRegExp re("\\d*");  
	if (!re.exactMatch(arg))
		return;

	UIhexPacketsPerRow = arg.toInt();

	reprintRawHex();
}

//todo: delete this when reworked hex
void exileSniffer::reprintRawHex()
{
	std::cout << "reprinting raw" << std::endl;
	ui.ptHexPane->clear();
	ui.ptASCIIPane->clear();

	clientHexData * client = get_clientdata(packetProcessor->getLatestDecryptProcess());
	if (!client)
		client = clients.begin()->second;
	vector <UI_RAWHEX_PKT *> pkts = client->rawHexPackets;

	rawCount_Recorded_Filtered.second = 0;

	for (auto pktIt = pkts.begin(); pktIt != pkts.end(); pktIt++)
	{
		UI_RAWHEX_PKT *pkt = *pktIt;

		if (packet_passes_decoded_filter(pkt->startBytes))
			output_hex_to_pane(pkt);
		else
			++rawCount_Recorded_Filtered.second;
	}
	updateRawFilterLabel();
}

void exileSniffer::updateRawFilterLabel()
{
	std::stringstream filterLabTxt;
	filterLabTxt << std::dec << rawCount_Recorded_Filtered.first << " Packets Recorded";
	if (rawCount_Recorded_Filtered.second)
		filterLabTxt << " / " << rawCount_Recorded_Filtered.second << " Filtered";
	ui.filterLabel->setText(QString::fromStdString(filterLabTxt.str()));
}

void exileSniffer::updateDecodedFilterLabel()
{
	if (refreshingFilters)
		ui.decodedDisplayedLabel->setText("Refreshing filters...");

	std::stringstream filterLabTxt;
	filterLabTxt << std::dec << "Packets ( Displayed: " << decodedCount_Displayed_Filtered.first <<
	" / Filtered: " << decodedCount_Displayed_Filtered.second <<
	" / Error: "<< decodedErrorPacketCount << " )";
	ui.decodedDisplayedLabel->setText(QString::fromStdString(filterLabTxt.str()));
}

void exileSniffer::toggleRawLineWrap(bool wrap)
{
	if (wrap)
	{
		ui.ptHexPane->setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);
		ui.ptASCIIPane->setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);
	}
	else
	{
		ui.ptHexPane->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
		ui.ptASCIIPane->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
	}

}


void exileSniffer::toggleRawAutoScroll(bool enabled)
{
	if (enabled)
	{
		ui.ptASCIIPane->moveCursor(QTextCursor::MoveOperation::End);
		ui.ptHexPane->moveCursor(QTextCursor::MoveOperation::End);
	}
}


void exileSniffer::decodedListClicked()
{
	//todo: user option to disable this
	if (ui.decodedAutoscrollCheck->isChecked())
		ui.decodedAutoscrollCheck->setChecked(false);
}

QString UI_DECODED_LIST_ENTRY::sender()
{
	if (flags & PKTBIT_OUTBOUND) return "["+QString::number(streamID)+"] Client";
	if (flags & PKTBIT_GAMESERVER) return "[" + QString::number(streamID) + "] GameServer";
	if (flags & PKTBIT_LOGINSERVER) return "[" + QString::number(streamID) + "] LoginServer";
	return "ErrorB";
}

void exileSniffer::decodedCellActivated(int row, int col)
{
	ui.decodedText->clear();

	QTableWidgetItem *item = ui.decodedListTable->item(row, 0);
	if (!item) return;
	UIDecodedPkt* obj = (UIDecodedPkt*)item->data(Qt::UserRole).value<UIDecodedPkt*>();

	if (!obj->decodeError())
	{
		map<unsigned short, actionFunc>* actionerList;
		if (obj->streamFlags & PKTBIT_GAMESERVER)
			actionerList = &gamePktActioners;
		else
			actionerList = &loginPktActioners;

		auto it = actionerList->find(obj->messageID);
		if (it != actionerList->end())
		{
			exileSniffer::actionFunc f = it->second;
			QString detailedAnalysis;
			(this->*f)(*obj, &detailedAnalysis);
			if(!detailedAnalysis.isEmpty())
				ui.decodedText->insertPlainText(detailedAnalysis + "\n\n");
			if (obj->wasAbandoned())
			{
				QString warn = "\tWARNING: Packet not decoded fully - processing abandoned\n\n";
				ui.decodedText->insertPlainText(warn);
			}
		}
		else
		{
			stringstream err;
			err << "ERROR! no action setup for displayed pkt id 0x" << std::hex << obj->messageID;
			add_metalog_update(QString::fromStdString(err.str()), obj->clientProcessID());
		}
	}


	if (!obj->originalbuf)
	{
		wstringstream err;
		err << "ERROR! Decodedcell item has no buffer set. pkt time: " 
			<< epochms_to_timestring(obj->time_processed_ms());
		add_metalog_update(QString::fromStdWString(err.str()), 0);
		return;
	}

	size_t msgSize;
	if (obj->decodeError())
		msgSize = obj->originalbuf->size() - obj->bufferOffsets.first;
	else
		msgSize = obj->bufferOffsets.second - obj->bufferOffsets.first;

	std::wstring serverName = (obj->streamFlags & PKTBIT_GAMESERVER) ? L"GameServer" : L"LoginServer";
	size_t bufStart = obj->bufferOffsets.first;
	long long pktTime = obj->time_processed_ms();

	ui.decodedRawHex->clear();
	ui.decodedRawText->clear();

	std::wstringstream hexdump;
	hexdump << epochms_to_timestring(pktTime);
	hexdump << " (start +" << msToQStringSeconds(startMSSinceEpoch, pktTime).toStdWString() << "s)" << std::endl;

	if (obj->streamFlags & PKTBIT_INBOUND)
		hexdump << serverName << " -> PlayerClient";
	else
		hexdump << "PlayerClient -> " << serverName;

	hexdump << std::setfill(L'0') << std::uppercase << L" ";
	hexdump << " (" << std::dec << msgSize << " bytes)" << std::endl;
	hexdump << std::endl;
	hexdump << " ";

	for (int i = 0; i < msgSize; ++i)
	{
		int index = bufStart + i;
		if (index >= obj->originalbuf->size()) break;
		byte item = obj->originalbuf->at(index);

		if (item)
			hexdump << " " << std::hex << std::setw(2) << (int)item;
		else
			hexdump << " 00";

		int nextIndex = i + 1;
		if ((nextIndex % UIhexPacketsPerRow == 0) && nextIndex < msgSize)
		{
			hexdump << std::endl;
			hexdump << " ";
		}
	}

	ui.decodedRawHex->insertPlainText(QString::fromStdWString(hexdump.str()));

	std::wstringstream asciiDump;
	asciiDump << std::setfill(L'0') << std::hex << std::setw(3);
	asciiDump << "\n\n\n 000:";
	for (int i = 0; i < msgSize; ++i)
	{
		int index = bufStart + i;
		if (index >= obj->originalbuf->size()) break;
		byte item = obj->originalbuf->at(index);

		if (item >= ' ' && item <= '~')
			asciiDump << (char)item;
		else
			asciiDump << '.';//replace unprintable with dots
		
		int nextIndex = i + 1;
		if ((nextIndex % UIhexPacketsPerRow == 0) && nextIndex < msgSize)
		{
			asciiDump << std::endl;
			asciiDump << " " << std::setw(3) << (i + 1) << ": ";
		}
	}

	ui.decodedRawText->insertPlainText(QString::fromStdWString(asciiDump.str()));
}


void exileSniffer::copySelected()
{
	QModelIndexList rowsSelected = ui.decodedListTable->selectionModel()->selectedRows();
	if (rowsSelected.empty()) return;
	QTableWidgetItem *rowitem = ui.decodedListTable->item(rowsSelected.front().row(), 0);

	//todo - mush stuff on this row together on keyboard
}

void exileSniffer::filterSelected()
{
	QModelIndexList rowsSelected = ui.decodedListTable->selectionModel()->selectedRows();
	if (rowsSelected.empty()) return;
	QTableWidgetItem *rowitem = ui.decodedListTable->item(rowsSelected.front().row(), 0);
	UIDecodedPkt* obj = (UIDecodedPkt*)rowitem->data(Qt::UserRole).value<UIDecodedPkt*>();

	//todo filter
}

void exileSniffer::decodedTableMenuRequest(QPoint pos)
{
	QMenu contextMenu(tr("Context menu"), this);

	QAction action1("Copy Contents", this);
	//connect(&action1, SIGNAL(triggered()), this, SLOT(copySelected()));
	contextMenu.addAction(&action1);

	//doesnt appear if nested in the if statements?
	QAction action2("", this);
	//connect(&action2, SIGNAL(triggered()), this, SLOT(filterSelected()));

	QModelIndexList rowsSelected = ui.decodedListTable->selectionModel()->selectedRows();
	if (rowsSelected.empty())
	{
		contextMenu.exec(mapToGlobal(pos));
		return;
	}

	QTableWidgetItem *rowitem = ui.decodedListTable->item(rowsSelected.front().row(), 0);
	UIDecodedPkt* obj = (UIDecodedPkt*)rowitem->data(Qt::UserRole).value<UIDecodedPkt*>();

	QString labeltext = "Filter PktID 0x" + QString::number(obj->messageID, 16);
	action2.setText(labeltext);
	contextMenu.addAction(&action2);
	contextMenu.exec(mapToGlobal(pos));
	return;
}


void exileSniffer::settingsSelectionChanged()
{
	int row = ui.settingsChoiceList->currentRow();
	ui.settingsStack->setCurrentIndex(row);
}

void exileSniffer::hashUtilInput()
{
	QString indata = ui.hashUtilInputText->text();
	indata.replace(" ", "");
	UINT32 testhash = indata.toULong(NULL, 16);

	std::string hashResult;
	std::string hashCategory;

	ui.order1hash->setText("0x"+QString::number(testhash,16));
	if (ggpk.lookup_hash(testhash, hashResult, hashCategory))
	{
		QString result = QString::fromStdString(hashCategory) + ": " + QString::fromStdString(hashResult);
		ui.order1hashres->setText(result);
	}
	else
		ui.order1hashres->setText("Not found");

	ui.order2hash->setText("0x" + QString::number(ntohl(testhash), 16));
	if (ggpk.lookup_hash(ntohl(testhash), hashResult, hashCategory))
	{
		QString result = QString::fromStdString(hashCategory) + ": " + QString::fromStdString(hashResult);
		ui.order2hashres->setText(result);
	}
	else
		ui.order2hashres->setText("Not found");
}