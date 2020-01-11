#ifndef NETWORK_NETWORKPRESENTERIMPL_HPP
#define NETWORK_NETWORKPRESENTERIMPL_HPP

#include "GamePresenter/NetworkPresenter.hpp"
#include "Network/Communicator.hpp"

namespace Network
{
class NetworkPresenterImpl : public GamePresenter::NetworkPresenter
{
public:
    NetworkPresenterImpl(Communicator &);
    virtual void send() override;

private:
    Communicator &communicator;
};
} // namespace Network

#endif // NETWORK_NETWORKPRESENTERIMPL_HPP
