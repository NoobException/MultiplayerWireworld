#ifndef NETWORK_COMMUNICATOR_HPP
#define NETWORK_COMMUNICATOR_HPP

#include "GamePresenter/NetworkPresenter.hpp"
#include "GameController/NetworkController.hpp"

namespace Network
{
class Communicator : public GamePresenter::NetworkPresenter
{
    public:
        Communicator(GameController::NetworkController &);
    private:
        GameController::NetworkController & network_controller;
};

} // Network


#endif // NETWORK_COMMUNICATOR_HPP