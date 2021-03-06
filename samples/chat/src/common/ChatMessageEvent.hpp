
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_SAMPLE_CHAT_COMMON_CHATMESSAGEEVENT
#define DUCTTAPE_SAMPLE_CHAT_COMMON_CHATMESSAGEEVENT

#include <Config.hpp>

#include <Network/NetworkEvent.hpp>
//#include <Event/MessageEvent.hpp>

class ChatMessageEvent : public dt::NetworkEvent/*, public dt::MessageEvent*/ {
public:
    ChatMessageEvent(const QString message, const QString sender);
    const QString getType() const;

    std::shared_ptr<dt::NetworkEvent> clone() const;
    void serialize(dt::IOPacket& p);

    const QString getSenderNick() const;
    const QString getMessageText() const;
protected:
    QString mSenderNick;

    QString mMessage;
};

#endif
