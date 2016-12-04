#include <QCoreApplication>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <databasecommunicator.h>

const unsigned short PORT = 5001;

std::string msgSend;

sf::TcpSocket socket;
sf::Mutex globalMutex;
bool quit = false;

sf::SocketSelector selector;
std::vector<sf::TcpSocket*> clients;
DatabaseCommunicator dbc("127.0.0.1" , "root" , "password");

//This method waits for input from the terminal to stop the server.
//Should be called on another thread to prevent blocking.
void GetInput(void)
{
    std::string s;
    std::cout << "\nEnter \"exit\" to quit." << std::endl;
    std::cin >> s;
    if(s == "exit")
        quit = true;
    globalMutex.lock();
    msgSend = s;
    globalMutex.unlock();
}

void Server(void)
{
    std::cout << "entered server" << std::endl;

    //start listening on specific port.
    sf::TcpListener listener;
    if (listener.listen(PORT) != sf::Socket::Done)
        return;

    std::cout << "Server is listening to port " << PORT << ", waiting for connections... " << std::endl;

    //The selector keeps track off all sockets (server and client side)
    selector.add(listener);

    //Start thread to accept input from terminal (cin)
    sf::Thread* thread = new sf::Thread(&GetInput);
    thread->launch();


    while(!quit)
    {
        //Makes selector wait on data coming from any socket.
        if(selector.wait())
        {
            //checks if the data came from the listener.
            if(selector.isReady(listener))
            {
                //listener is ready to accept a clien.
                sf::TcpSocket* client = new sf::TcpSocket;
                if(listener.accept(*client) == sf::Socket::Done)
                {
                    std::cout << "Client connected: " << client->getRemoteAddress() << std::endl;
                    //keep track of pointers to clients.
                    clients.push_back(client);

                    selector.add(*client);
                }
                else
                {
                    //delete client if it wasn't accepted correctly to avoid memory leaks.
                    delete client;
                }
            }
            //data was from a client socket.
            else
            {
                //iterate over every socket for data coming in.
                for(std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket& client = **it;

                    //data is coming from client.
                    if(selector.isReady(client))
                    {
                        sf::Packet packet;
                        std::string s;
                        if(client.receive(packet) == sf::Socket::Done)
                        {
                            //extrude packet into string and print (Testing purposes)
                            packet >> s;
                            std::cout << s << std::endl;

                            ///TEST CODE

                            QString enteredUName = QString(s.c_str());
                            int uID = dbc.addStudent(enteredUName , "1234" , "JohnnyJohnson" , true , "idk");

                            StudentInfo info = dbc.getStudentInfo(uID);
                            std::cout << "isValid? " << (info.isValid ? "True" : "False") << std::endl << std::endl;

                            if(info.isValid)
                            {
                                std::cout << (info.username.toStdString()) << std::endl;
                                std::cout << (info.password.toStdString()) << std::endl;
                                std::cout << (info.userID) << std::endl;
                                std::cout << (info.classCode.toStdString()) << std::endl;
                                std::cout << (info.realName.toStdString()) << std::endl;
                                std::cout << "isTeacher? " << (info.isTeacher ? "True" : "False") << std::endl << std::endl;

                                std::cout << dbc.addGame(info.userID, 2056 , 477) << std::endl;
                                std::cout << dbc.addGame(info.userID, 10000 , 12) << std::endl;
                                std::cout << dbc.addGame(info.userID, 7944 , 13) << std::endl;
                                std::cout << dbc.addGame(info.userID, 875323 , 37) << std::endl;
                                std::cout << dbc.addGame(info.userID, 2500 , 137) << std::endl;

                                std::cout << dbc.getHighScore(info.userID).score << std::endl;
                                std::cout << dbc.getHighScore(info.userID).level << std::endl;

                                std::cout << "Bad user returns a valid game? " << (dbc.getHighScore(info.userID + 90).isValid ? "True" : "False") << std::endl;

                                std::cout << dbc.getTotalScore(info.userID + 83) << std::endl;

                                std::cout << dbc.getAverageScore(info.userID) << std::endl;
                                std::cout << dbc.getAverageScore(info.userID + 342) << std::endl;
                            }

                            if(dbc.loginUser(enteredUName, "1234") >= 0)
                            {
                                std::cout << "Logged in as " << enteredUName.toStdString() << std::endl;
                            }
                            else
                            {
                                std::cout << "Invalid username or password." << std::endl;
                            }
                            ///TEST CODE
                        }

                        //send back to client that it was received.
                        if(s.size() != 0)
                        {
                            sf::Packet sendPacket;
                            sendPacket << "received";
                            if(client.send(sendPacket) != sf::Socket::Done)
                            {
                                std::cout << "Couldn't send message" << std::endl;
                            }
                        }
                    }
                }
            }
        }

    }

    //if we are still waiting on a thread, we wait and delete.
    if(thread)
    {
        thread->wait();
        delete thread;
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server();

    return 0;
}
