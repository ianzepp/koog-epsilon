#ifndef IONAPSTERCODES_H
#define IONAPSTERCODES_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/**
  *@author Ian Zepp
  */

class IONapsterCodes
{
protected:
	IONapsterCodes()        {};
	~IONapsterCodes()       {};

public:
        // Napster codes
        //
        // these codes range from 0 to 999
        enum {
                ServerError             = 0,
                LoginRequest            = 2,
                LoginReply              = 3,
                LoginCreate             = 6,
                LoginOptions            = 14,

                UpgradeRequest          = 4,
                UpgradeReply            = 5,

                RegisteredRequest       = 7,
                RegisteredReply         = 9,
                RegisteredError         = 8,
                RegisteredInvalid       = 10,

                ServerEcho              = 13,

                // series 100
                SharedAdd               = 100,
                SharedRemove            = 102,
                SharedRemoveAll         = 110,

                // series 200
                SearchRequest           = 200,
                SearchReply             = 201,
                SearchDone              = 202,

                DownloadRequest         = 203,
                DownloadReply           = 204,
                DownloadError           = 206,

                UserMessageRequest      = 205,
                UserMessageReply        = 205,

                HotlistAddRequest       = 207,
                HotlistAddReply         = 301,
                HotlistAddError         = 302,
                HotlistRemoveRequest    = 303,

                HotlistInit             = 208,
                HotlistLogon            = 209,
                HotlistLogoff           = 210, // doubled

                BrowseError             = 210, // doubled
                BrowseRequest           = 211,
                BrowseReply             = 212,
                BrowseDone              = 213,

                ServerStats             = 214,

                DownloadStarted         = 218,
                DownloadDone            = 219,
                UploadStarted           = 220,
                UploadDone              = 221,

                // series 300
                IgnoreListRequest       = 320, // from client
                IgnoreListReply         = 321,
                IgnoreListDone          = 320, // from server

                // series 400
                GeneralError            = 404,

                // channel codes

                ChanJoinRequest         = 400,
                ChanJoinReply           = 405,
                ChanPartRequest         = 401,
                ChanMessageRequest      = 402,
                ChanEmoteRequest        = 824, // from client

                ChanList                = 408,
                ChanListDone            = 409,

                ChanMessage             = 403,
                ChanJoin                = 406,
                ChanPart                = 407,
                ChanTopic               = 410,
                ChanEmote               = 824, // from server

                ChanBanListRequest      = 420, // from client
                ChanBanListReply        = 421,
                ChanBanListDone         = 420, // from server
                ChanBan                 = 422,
                ChanUnban               = 423,
                ChanClearBans           = 424,
                ChanMotd                = 425,

                // series 500
                FWDownloadRequest       = 500,
                FWDownloadReply         = 501,

                // series 600
                SpeedRequest            = 600,
                SpeedReply              = 601,

                WhoisRequest            = 603,
                WhoisReply              = 604,
                WhoisError              = 605, // doubled
                WhowasReply             = 605, // doubled

                UploadRequest           = 607,
                UploadReply             = 608,
                UploadError             = 609,

                KillUser                = 610,
                ResetPortRequest        = 613, // also see 703

                ServerBanListRequest    = 615, // from client
                ServerBanListReply      = 616,
                ServerBanListDone       = 615, // from server

                ListChansRequest        = 617, // from client
                ListChansReply          = 618,
                ListChansDone           = 617, // from server

                QueueLimitRequest       = 619, // from client
                QueueLimitReply         = 620, // from server

                SystemMessageRequest    = 621,
                SystemMessageReply      = 621,

                DataPortError           = 626,

                OpMessageRequest        = 627, // from client
                OpMessageReply          = 627, // from server
                GlobalMessageRequest    = 628, // from client
                GlobalMessageReply      = 628, // from server

                // series 700
                ChangeSpeedRequest      = 700,
                ChangePasswordRequest   = 701,
                ChangeEmailRequest      = 702,
                ChangePortRequest       = 703,

                AnotherLogin            = 748,
                ServerPingRequest       = 750,
                ServerPingReply         = 750,
                ClientPingRequest       = 751,
                ClientPingReply         = 752,

                // series 800
                RedirectClientRequest   = 821,
                CycleClientRequest      = 822,

                ChangeChannelLimit      = 826,
                ChangeChannelLevel      = 823,

                ListAllChansRequest     = 827,
                ListAllChansReply       = 828,
                ListAllChansDone        = 827,

                ChanKickbanUser         = 829,

                ChanUsersRequest        = 830,
                ChanUsersReply          = 825,
                ChanUsersDone           = 830,

                // special codes
                SocketHostFound         = 20001,
                SocketConnected         = 20002,
                SocketConnectionClosed  = 20003,
                SocketError             = 20004,

                // no entry
                __null_entry            = 99999
        };
};

#endif

