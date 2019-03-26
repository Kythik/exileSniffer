#pragma once

#include <QtWidgets/QMainWindow>


#include "packet_capture_thread.h"
#include "key_grabber_thread.h"
#include "json_pipe_thread.h"
#include "packet_processor.h"
#include "uiMsg.h"
#include "clientHexData.h"
#include "gameDataStore.h"

#include "ui_exileSniffer.h"

#include "filterForm.h"
#include "ui_rawfilterform.h"
#include <fstream>

#define DECODED_SECTION_TIME 0
#define DECODED_SECTION_SENDER 1
#define DECODED_SECTION_MSGID 2
#define DECODED_SECTION_SUMMARY 3


struct RAW_FILTERS {
	bool filterIncoming = false;
	bool filterOutgoing = false;
	bool filterGame = false;
	bool filterLogin = false;
	vector <pair<short, streamType>> packets;
};

class exileSniffer : public QMainWindow
{
	Q_OBJECT

	public:
		exileSniffer(QWidget *parent = Q_NULLPTR);
		~exileSniffer() {
			pipeThread->close();
			if (packetProcessor) packetProcessor->running = false;
			if (packetSniffer) packetSniffer->stop_sniffing();
			if (keyGrabber) keyGrabber->running = false;
			if (pipeThread) pipeThread->running = false;
			while (!keyGrabber->ded || !packetProcessor->ded || !packetSniffer->ded || !pipeThread->ded)
				Sleep(6);
		}
	
	private slots:
		void read_UI_Q();

		void showRawFiltersDLG() { filterFormObj.isHidden() ? filterFormObj.show() : filterFormObj.hide(); }

		void toggleDecodedAutoScroll(bool enabled);
		void decodedListClicked();
		void decodedCellActivated(int, int);
		void decodedTableMenuRequest(QPoint);
		void copySelected();
		void filterSelected();
		void stopDecrypting();
		void resumeScanningEvent();
		void settingsSelectionChanged(); 
		void hashUtilInput();
		void updateSettings(); 
		void doLogSetDir();
		void doLogOpenDir();

	private:

		bool load_messagetypes_json();
		void setup_settings_tab();
		void save_settings();
		void setup_decoded_messages_tab();
		void setup_decryption_tab();
		void setLabelActive(QLabel *lab, bool state);
		void set_keyEx_scanning_count(int total, int scanning);
		void updateStreamStateWidget();
		void setStateDecrypting(int streamID);
		void setStateNotDecrypting(); 
		void action_ended_stream(int streamID);
		void handle_stream_event(UI_STREAMEVENT_MSG *streamNote);
		void handle_client_event(UI_CLIENTEVENT_MSG *cliEvtMsg);
		void output_hex_to_file(UI_RAWHEX_PKT *pkt, std::ofstream& file);

		void init_gamePkt_Actioners();
		void init_loginPkt_Actioners();

		void start_threads();
		void initFilters(); 

		void action_UI_Msg(UI_MESSAGE *msg);
		void add_metalog_update(QString msg, DWORD pid);
		void handle_raw_packet_data(UI_RAWHEX_PKT *pkt);
		void action_undecoded_packet(UIDecodedPkt& decoded);
		void action_decoded_packet(UIDecodedPkt& decoded);
		void action_decoded_game_packet(UIDecodedPkt& decoded);
		void action_decoded_login_packet(UIDecodedPkt& decoded);
		
		clientHexData * get_clientdata(DWORD pid);
		void addDecodedListEntry(UIDecodedPkt *obj, bool isNewEntry = true);
		void setRowColor(int row, QColor colour);

		bool packet_passes_decoded_filter(ushort msgID);
		void updateDecodedFilterLabel();

		QString stringify_eventslist(WValue &eventlist);
		QString stringify_eventslist_2(WValue &eventlist);

		bool eventFilter(QObject *obj, QEvent *event);
		
	private:

		void action_LOGIN_CLI_KEEP_ALIVE(UIDecodedPkt&, QString*);
		void action_LOGIN_EPHERMERAL_PUBKEY(UIDecodedPkt&, QString *);
		void action_LOGIN_CLI_AUTH_DATA(UIDecodedPkt&, QString*);
		void action_LOGIN_SRV_UNK0x4(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_RESYNC(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_CHANGE_PASSWORD(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_DELETE_CHARACTER(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_CHARACTER_SELECTED(UIDecodedPkt&, QString*);
		void action_LOGIN_SRV_NOTIFY_GAMESERVER(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_CREATED_CHARACTER(UIDecodedPkt&, QString*);
		void action_LOGIN_SRV_CHAR_LIST(UIDecodedPkt&, QString*);
		void action_LOGIN_SRV_FINAL_PKT(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_REQUEST_RACE_DATA(UIDecodedPkt&, QString*);
		void action_LOGIN_SRV_LEAGUE_LIST(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_REQUEST_LEAGUES(UIDecodedPkt&, QString*);
		void action_LOGIN_CLI_UNK0x24(UIDecodedPkt&, QString *);

		void action_SRV_PKT_ENCAPSULATED(UIDecodedPkt&, QString*);
		void action_CLI_CHAT_MSG_ITEMS(UIDecodedPkt&, QString*);
		void action_CLI_CHAT_MSG(UIDecodedPkt&, QString*);
		void action_CLI_CHAT_COMMAND(UIDecodedPkt&, QString*);
		void action_SRV_CHAT_MESSAGE(UIDecodedPkt&, QString*);
		void action_SRV_SERVER_MESSAGE(UIDecodedPkt&, QString*);
		void action_CLI_LOGGED_OUT(UIDecodedPkt&, QString*);
		void action_CLI_HNC(UIDecodedPkt&, QString*);
		void action_SRV_HNC(UIDecodedPkt&, QString*);
		void action_SRV_AREA_INFO(UIDecodedPkt&, QString*);

		void action_SRV_PRELOAD_MONSTER_LIST(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0x13(UIDecodedPkt&, QString *);
		void action_SRV_ITEMS_LIST(UIDecodedPkt&, QString*);
		void action_CLI_CLICKED_GROUND_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_ACTION_PREDICTIVE(UIDecodedPkt&, QString*);
		void action_SRV_TRANSFER_INSTANCE(UIDecodedPkt& obj, QString *analysis);
		void action_SRV_INSTANCE_SERVER_DATA(UIDecodedPkt&, QString*);
		void action_CLI_PICKUP_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_PLACE_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_DROP_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_REMOVE_SOCKET(UIDecodedPkt&, QString*);
		void action_CLI_INSERT_SOCKET(UIDecodedPkt&, QString*);

		void action_CLI_LEVEL_SKILLGEM(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0x20(UIDecodedPkt&, QString*);
		void action_CLI_SKILLPOINT_CHANGE(UIDecodedPkt&, QString*);

		void action_CLI_CHOSE_ASCENDANCY(UIDecodedPkt&, QString*);

		void action_CLI_MERGE_STACK(UIDecodedPkt&, QString*);
		void action_CLI_CANCEL_BUF(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0x2c(UIDecodedPkt&, QString*);
		void action_CLI_SELECT_MAPTRAVEL(UIDecodedPkt&, QString*);
		void action_CLI_SET_HOTBARSKILL(UIDecodedPkt&, QString*);
		void action_SRV_SKILL_SLOTS_LIST(UIDecodedPkt&, QString*);
		void action_CLI_REVIVE_CHOICE(UIDecodedPkt&, QString*);
		void action_SRV_YOU_DIED(UIDecodedPkt&, QString*);
		void action_CLI_ACTIVATE_ITEM(UIDecodedPkt&, QString*);
		
		void action_CLI_USE_BELT_SLOT(UIDecodedPkt&, QString*);
		void action_CLI_USE_ITEM_ON_ITEM(UIDecodedPkt&, QString*);
		void action_CLI_USE_ITEM_ON_OBJ(UIDecodedPkt&, QString*);
		void action_CLI_UNK_0x41(UIDecodedPkt&, QString*);
		void action_CLI_UNK_0x42(UIDecodedPkt&, QString*);

		void action_CLI_SELECT_NPC_DIALOG(UIDecodedPkt&, QString*);
		void action_SRV_SHOW_NPC_DIALOG(UIDecodedPkt&, QString*);
		void action_CLI_CLOSE_NPC_DIALOG(UIDecodedPkt&, QString*);

		void action_SRV_OPEN_UI_PANE(UIDecodedPkt&, QString*);
		void action_CLI_SPLIT_STACK(UIDecodedPkt&, QString*);
		void action_SRV_LIST_PORTALS(UIDecodedPkt&, QString*);
		void action_CLI_SEND_PARTY_INVITE(UIDecodedPkt&, QString*);

		void action_CLI_TRY_JOIN_PARTY(UIDecodedPkt&, QString*);
		void action_CLI_DISBAND_PUBLIC_PARTY(UIDecodedPkt&, QString*);
		void action_CLI_CREATE_PUBLICPARTY(UIDecodedPkt&, QString*);
		void action_CLI_UNK_x57(UIDecodedPkt&, QString*);
		void action_CLI_GET_PARTY_DETAILS(UIDecodedPkt&, QString*);
		void action_SRV_FRIENDSLIST(UIDecodedPkt&, QString*);

		void action_SRV_PARTY_DETAILS(UIDecodedPkt&, QString*);
		void action_SRV_PARTY_ENDED(UIDecodedPkt&, QString *);
		void action_CLI_REQUEST_PUBLICPARTIES(UIDecodedPkt&, QString*);
		void action_SRV_PUBLIC_PARTY_LIST(UIDecodedPkt&, QString*);

		void action_CLI_MOVE_ITEM_PANE(UIDecodedPkt&, QString*);

		void action_CLI_CONFIRM_SELL(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0x68(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0x69(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0x6d(UIDecodedPkt&, QString*);
		void action_SRV_CREATE_ITEM(UIDecodedPkt&, QString*);
		void action_SRV_SLOT_ITEMSLIST(UIDecodedPkt&, QString*);
		void action_SRV_INVENTORY_SET_REMOVE(UIDecodedPkt&, QString *);
		void action_SRV_GRANTED_XP(UIDecodedPkt&, QString*);
		void action_CLI_SELECT_STASHTAB(UIDecodedPkt&, QString*);
		void action_SRV_STASHTAB_DATA(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0x74(UIDecodedPkt&, QString*);
		void action_CLI_SET_STATUS_MESSAGE(UIDecodedPkt&, QString*);
		void action_SRV_MOVE_OBJECT(UIDecodedPkt&, QString*);

		void action_CLI_ACTIVATE_MAP(UIDecodedPkt&, QString*);
		void action_CLI_SWAPPED_WEAPONS(UIDecodedPkt&, QString*);

		void action_SRV_ADJUST_LIGHTING(UIDecodedPkt&, QString*);
		void action_CLI_TRANSFER_ITEM(UIDecodedPkt&, QString*);

		void action_SRV_INVENTORY_FULL(UIDecodedPkt&, QString*);

		void action_SRV_PVP_MATCHLIST(UIDecodedPkt&, QString*);
		void action_SRV_EVENTSLIST(UIDecodedPkt&, QString*);

		void action_CLI_SKILLPANE_ACTION(UIDecodedPkt&, QString*);
		void action_SRV_ACHIEVEMENT_1(UIDecodedPkt&, QString*);
		void action_SRV_ACHIEVEMENT_2(UIDecodedPkt&, QString*);

		void action_SRV_SKILLPANE_DATA(UIDecodedPkt&, QString*);
		void action_SRV_UNK_POSITION_LIST(UIDecodedPkt&, QString*);

		void action_CLI_MICROTRANSACTION_SHOP_ACTION(UIDecodedPkt&, QString*);
		void action_SRV_MICROTRANSACTION_SHOP_DETAILS(UIDecodedPkt&, QString*);
		void action_CLI_UNK_A4(UIDecodedPkt&, QString*);

		void action_SRV_CHAT_CHANNEL_ID(UIDecodedPkt&, QString*);

		void action_SRV_UNK_A6(UIDecodedPkt&, QString*); 
		void action_SRV_UNK_0xA7(UIDecodedPkt&, QString*);

		void action_SRV_GUILD_MEMBER_LIST(UIDecodedPkt&, QString*);

		void action_CLI_GUILD_CREATE(UIDecodedPkt&, QString*);


		void action_CLI_EXIT_TO_CHARSCREEN(UIDecodedPkt&, QString*);
		void action_SRV_LOGINSRV_CRYPT(UIDecodedPkt&, QString*);
		void action_CLI_DUEL_CHALLENGE(UIDecodedPkt&, QString*);
		void action_SRV_DUEL_RESPONSE(UIDecodedPkt&, QString*);
		void action_SRV_DUEL_CHALLENGE(UIDecodedPkt&, QString*);
		void action_CLI_UNK_0xC7(UIDecodedPkt&, QString*);
		void action_CLI_UNK_0xC8(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0xCB(UIDecodedPkt&, QString*);

		void action_SRV_EVENTSLIST_2(UIDecodedPkt&, QString*);

		void action_CLI_USED_SKILL(UIDecodedPkt&, QString*);

		void action_CLI_CLICK_OBJ(UIDecodedPkt&, QString*);
		void action_CLI_MOUSE_HELD(UIDecodedPkt&, QString*);
		void action_SRV_NOTIFY_AFK(UIDecodedPkt&, QString*);
		void action_CLI_MOUSE_RELEASE(UIDecodedPkt&, QString*);

		void action_CLI_OPEN_WORLD_SCREEN(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0xE5(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0xE7(UIDecodedPkt&, QString*);	
		void action_SRV_OBJ_REMOVED(UIDecodedPkt&, QString*);
		void action_SRV_MOBILE_START_SKILL(UIDecodedPkt&, QString*);
		void action_SRV_MOBILE_FINISH_SKILL(UIDecodedPkt&, QString*);

		void action_SRV_MOBILE_UNK_0xef(UIDecodedPkt&, QString*);
		void action_SRV_MOBILE_UNK_0xf0(UIDecodedPkt&, QString*);
		void action_SRV_MOVE_CHANNELLED(UIDecodedPkt&, QString*);
		void action_SRV_END_CHANNELLED(UIDecodedPkt&, QString*);
		void action_SRV_MOBILE_UPDATE_HMS(UIDecodedPkt&, QString*);
		void action_SRV_STAT_CHANGED(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0xf3(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0xf4(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0xf6(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0xf7(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0xf8(UIDecodedPkt&, QString*);
		void action_SRV_UNK_0xf9(UIDecodedPkt&, QString*);

		void action_SRV_START_BUFF(UIDecodedPkt&, QString*);
		void action_SRV_END_EFFECT(UIDecodedPkt&, QString*);

		void action_SRV_EVENT_TRIGGERED(UIDecodedPkt&, QString*);

		void action_SRV_UNK_0x107(UIDecodedPkt&, QString*); 
		
		void action_SRV_UNK_0x109(UIDecodedPkt&, QString*);

		void action_CLI_FINISHED_LOADING(UIDecodedPkt&, QString *);
		void action_SRV_NOTIFY_PLAYERID(UIDecodedPkt&, QString *);

		void action_SRV_UNKNOWN_0x112(UIDecodedPkt&, QString*);
		void action_SRV_UNKNOWN_0x119(UIDecodedPkt&, QString*);
		void action_CLI_OPTOUT_TUTORIALS(UIDecodedPkt&, QString*);
		void action_SRV_BESTIARY_CAPTIVES(UIDecodedPkt&, QString*);
		void action_CLI_OPEN_BESTIARY(UIDecodedPkt&, QString*);
		void action_SRV_BESTIARY_UNLOCKED_LIST(UIDecodedPkt&, QString*);
		void action_SRV_SHOW_ENTERING_MSG(UIDecodedPkt&, QString*);
		void action_SRV_HEARTBEAT(UIDecodedPkt&, QString*);
		void action_SRV_ADD_OBJECT(UIDecodedPkt&, QString*);
		void action_SRV_UPDATE_OBJECT(UIDecodedPkt&, QString*);
		void action_SRV_IDNOTIFY_0x138(UIDecodedPkt&, QString*);
		
	private:
		Ui::exileSniffer ui;
		Ui::rawFilterForm rawFiltersFormUI;
		filterForm filterFormObj;

		QSettings *settings = new QSettings("ExileSniffer", "Settings");
		bool doLogging = true, doPipe = true;
		QString pipeName;
		QDir logDir;
		unsigned int metalogEntries = 0;

		std::pair <unsigned long, unsigned long> rawCount_Recorded_Filtered;
		std::pair <int, int> decodedCount_Displayed_Filtered;	 //table row index is int
		int decodedErrorPacketCount = 0;
		
		SafeQueue<UI_MESSAGE *> uiMsgQueue; //read by ui thread, written by all others
		SafeQueue<GAMEPACKET > gamePktQueue, loginPktQueue;
		map<DWORD, clientHexData *> clients;
		map<int, eStreamState> streamStates;
		//id of an ending stream if we expect a new one soon
		int transitionStream = -1; 
		int latestDecryptingStream = -1;
		std::pair<int, int> active_total_ClientScanCount = make_pair(0,0);

		typedef void (exileSniffer::*actionFunc)(UIDecodedPkt&, QString*);
		map<unsigned short, actionFunc> gamePktActioners;
		map<unsigned short, actionFunc> loginPktActioners;
		
		std::vector<UIDecodedPkt *> decodedListEntries;

		const long long startMSSinceEpoch = ms_since_epoch();
		bool activeDecryption = false;

private:
	rapidjson::Document messageTypes;
	rapidjson::GenericValue<rapidjson::UTF8<>> *loginMessageTypes = NULL;
	rapidjson::GenericValue<rapidjson::UTF8<>> *gameMessageTypes = NULL;
	
private:
	packet_capture_thread* packetSniffer;
	key_grabber_thread* keyGrabber;
	packet_processor* packetProcessor;
	json_pipe_thread* pipeThread;
	gameDataStore *ggpk;
};

