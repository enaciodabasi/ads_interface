#ifndef ADS_INTERFACE_HPP
#define ADS_INTERFACE_HPP

#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <unordered_map>


#include "AdsLib.h"
#include "AdsVariable.h"
#include "AmsConnection.h"

namespace ads_interface
{
    class Interface
    {
        public:

        Interface(
            const std::string& remote_ipv4,
            const std::string& remote_net_id
        );

        ~Interface();

        template<typename T>
        T read(const std::string& container_name, const std::string& variable_to_read_name);

        protected:

        std::string m_RemoteIpv4;

        std::string m_RemoteNetIdAddres;

        std::shared_ptr<AdsDevice> m_Route;

        AmsNetId m_RemoteNetId;

        bool check_state();

        private:

        int m_AdsState;

        bool m_DeviceState;

        void init_ads_device();

    };

    template<typename T>
    T read(const std::string& container_name, const std::string& variable_to_read_name)
    {
        
    }
}

#endif