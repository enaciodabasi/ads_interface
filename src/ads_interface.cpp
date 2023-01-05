#include "../include/ads_interface/ads_interface.hpp"

namespace ads_interface
{
    Interface::Interface(
        const std::string& remote_ipv4,
        const std::string& remote_net_id
    ) : m_RemoteIpv4(remote_ipv4), m_RemoteNetIdAddres(remote_net_id)
    {
        m_RemoteNetId = AmsNetId(m_RemoteNetIdAddres);

        m_Route = std::make_shared<AdsDevice>(
            m_RemoteIpv4,
            m_RemoteNetId,
            AMSPORT_R0_PLC_TC3  
        );

    }
    
    bool Interface::check_state()
    {
        const auto state = m_Route->GetState();
       
        
    }

    void Interface::init_ads_device()
    {
        m_RemoteNetId = AmsNetId(m_RemoteNetIdAddres);

        m_Route = std::make_shared<AdsDevice>(
            m_RemoteIpv4,
            m_RemoteNetId,
            AMSPORT_R0_PLC_TC3  
        );
    }
}
