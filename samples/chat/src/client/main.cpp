
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Config.hpp>

#include "Client.hpp"

#include <Utils/Utils.hpp>

#include <ctime>
#include <iostream>

int main(int argc, char** argv) {
    dt::Game game;
    Client* client = new Client();

    if(argc > 1)
        client->setNick(argv[1]);
    else
        client->setNick("chatter-" + dt::Utils::toString(time(0)));

    if(argc > 2)
        client->setServerIP(sf::IpAddress(argv[2]));

    game.run(client, argc, argv);

    return 0;
}
