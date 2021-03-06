
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include "ConnectionsTest/ConnectionsTest.hpp"

namespace ConnectionsTest {

bool ConnectionsTest::run(int argc, char** argv) {
    std::map<uint16_t, dt::Connection::ConnectionSP> connections;
    dt::ConnectionsManager connections_manager;

    uint16_t max_connections = 50;
    connections_manager.setMaxConnections(max_connections); // counts from 1

    // Test AddConnection()
    for(uint8_t i = 0; i <= max_connections; ++i) { // this will get us up to 21 connections
        uint16_t ip = dt::Random::get(1, 255);
        uint16_t port = dt::Random::get(1001, 51311);

        dt::Connection::ConnectionSP connection(new dt::Connection(sf::IpAddress("127.168.178." + dt::Utils::toStdString(dt::Utils::toString(ip))), port+i));
        uint16_t connection_id = connections_manager.addConnection(connection);
        if(connection_id != 0) {
           connections[connection_id] = connection;

          // Test GetConnection()
          if(!(connections[connection_id]->getIPAddress() == connections_manager.getConnection(connection_id)->getIPAddress() && \
                       connections[connection_id]->getPort() == connections_manager.getConnection(connection_id)->getPort())) {  
               std::cerr << "Connections should be equal." << std::endl;
               return false;
           } else {
               // Test GetConnectionID()
               dt::Connection::ConnectionSP tmp_connection = connections_manager.getConnection(connection_id);
               if(tmp_connection != nullptr) {
                   if(connection_id != connections_manager.getConnectionID(*(tmp_connection))) {
                       std::cerr << "Connection IDs should be equal." << std::endl;
                       return false;
                   }
               } else {
                   std::cerr << "ConnectionsManager returned unknown connection ID." << std::endl;
                   return false;
               }
           }

           if(i >= max_connections) {
               std::cerr << "ConnectionsManager did allow too many connections." << std::endl;
               return false;
           }

        } else {
            if(i != max_connections) {
                std::cerr << "ConnectionsManager failed to add a connection." << std::endl;
                return false;
            }
        }
    }

    // Test IsKnownConnection()
    for(auto iter = connections.begin(); iter != connections.end(); ++iter) {
        if(!connections_manager.isKnownConnection(*(iter->second))) {
            std::cerr << "ConnectionsManager should know the requested connection." << std::endl;
            return false;
        }
    }

    // Test RemoveConnection()
    int i = 0;
    for(auto iter = connections.begin(); iter != connections.end(); ++iter) {
        if(i<=10) {
            connections_manager.removeConnection(iter->first);
            if(connections_manager.getConnection(iter->first) != nullptr) {
                std::cerr << "ConnectionsManager did not delete correctly using the ID." << std::endl;
                return false;
            }
        } else {
            connections_manager.removeConnection(*(iter->second));
            if(connections_manager.getConnectionID(*(iter->second)) != 0) {
                std::cerr << "ConnectionsManager did not delete correctly using the connection instance." << std::endl;
                return false;
            }
        }
        ++i;
    }
    return true;
}


QString ConnectionsTest::getTestName() {
    return "Connections";
}

}
