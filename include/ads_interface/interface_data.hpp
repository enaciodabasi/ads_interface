#ifndef INTERFACE_DATA_HPP
#define INTERFACE_DATA_HPP

#include <iostream>
#include <memory>

#include "AdsVariable.h"

namespace ads_interface
{   

    template<typename T>
    class Data
    {
        public:

        Data(
            const std::string& variable_symbol
        );
        
        /*
            @brief Creates a new Data object with type T.
            @param variable_symbol: Symbol name in the Beckhoff System.
            @param route: shared_ptr to an AdsDevice object, used for creating a weak_ptr of the same type.
        */
        Data(
            const std::string& variable_symbol,
            const std::shared_ptr<AdsDevice>& route
        );

        // Copy constructor
        Data(
            const Data& data
        )
        {}
        Data& operator=(const Data& data)
        {
            return *this;
        }

        ~Data();

        /*
            @brief Writes a new value to ADS.
            @param new_value: Value of type T to write.
        */
        void setValue(T new_value);

        private:

        // Symbol name in the Beckhoff System to use in ADS
        std::string m_VariableSymbol;

        std::weak_ptr<AdsDevice> m_Route;

        // AdsVariable to write and read the value.
        AdsVariable<T>* m_AdsData = nullptr;
        
    };  

    template<typename T>
    Data<T>::Data(
        const std::string& variable_symbol
    )
    {
        //std::cout << "Created data of type " << typename(T) << std::endl;
    }

    template<typename T>
    Data<T>::Data(
        const std::string& variable_symbol,
        const std::shared_ptr<AdsDevice>& route
    ) : m_VariableSymbol(variable_symbol)
    {
        //m_AdsData = new AdsVariable<T>(route, m_VariableSymbol);
        m_Route = route;
    }
    
    template<typename T>
    Data<T>::~Data()
    {
        std::cout << "Data deleted." << std::endl;
        if(m_AdsData != nullptr)
        {   
             
            delete m_AdsData;
        }
    }

    template<typename T>
    void Data<T>::setValue(T new_value)
    {
        std::shared_ptr<AdsDevice> tempRouteSharedPtr = m_Route.lock();
        
        if(m_AdsVar == nullptr)
        {
            
            try{
                if(tempRouteSharedPtr)
                    m_AdsVar = new AdsVariable<T>(*tempRouteSharedPtr, symbol_name);
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