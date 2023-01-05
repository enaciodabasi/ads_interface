#ifndef DATA_ARRAY_HPP
#define DATA_ARRAY_HPP

#include <iostream>
#include <memory>
#include <array>

#include "AdsDevice.h"
#include "AdsVariable.h"

namespace ads_interface
{   
    // Use this class when you want to write a fixed size array of size N with type T.
    template<typename T, size_t N> 
    class DataArray
    {
        public:

        /*
            @brief Creates a DataArray object that can write a fixed size array to ADS.
            @param symbol_name: Name of the symbol to write to in the Beckhoff system.
            @param route: AdsDevice shared_ptr
        */
        DataArray(
            const std::string& symbol_name,
            const std::shared_ptr<AdsDevice>& route
        );

        ~DataArray();

        /*
            @brief Writes new_val to ADS via a AdsVariable.
            @param new_val: Array to write to ADS.
        */
        void setValue(const std::array<T, N>& new_val)

        private:

        // Symbol name in the Beckhoff System.
        std::string m_SymbolName;

        // Weak Pointer to the AdsDevice
        std::weak_ptr<AdsDevice> m_Route;

        std::array<T, N> m_Value;
        
        // Pointer to an AdsVariable
        AdsVariable<std::array<T, N>>* m_AdsVar;
        
    };

    template<typename T, size_t N>
    DataArray<T, N>::DataArray(
        const std::string& symbol_name,
        const std::shared_ptr<AdsDevice>& route
    )   : m_SymbolName(symbol_name)
    {
        m_Route = route;
    }

    template<typename T, size_t N>
    DataArray<T, N>::~DataArray()
    {
        if(m_AdsVar != nullptr)
        {
            delete m_AdsVar;
        }
    } 

    template<typename T, size_t N>
    void DataArray<T, N>::setValue(const std::array<T, N>& new_val)
    {
        std::shared_ptr<AdsDevice> tempRouteSharedPtr = m_Route.lock();
        if(m_AdsVar == nullptr)
        {
            
            try{
                if(tempRouteSharedPtr)
                    m_AdsVar = new AdsVariable<std::array<T, N>>(*tempRouteSharedPtr, symbol_name);
            }catch(AdsException& ex){
                std::cout << ex.what() << std::endl;
            }catch(std::system_error& ex){
                std::cout << ex.what() << std::endl;
            }
        }

        *m_AdsVar = new_val;

        // Clean up the ADS variable so that it doesn't constantly write to ADS.
        delete m_AdsVar;
        m_AdsVar = nullptr;

    }
}

#endif