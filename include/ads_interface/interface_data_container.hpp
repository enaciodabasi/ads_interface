#ifndef INTERFACE_DATA_CONTAINER_HPP
#define INTERFACE_DATA_CONTAINER_HPP

#include <iostream>
#include <vector>
#include <variant>
#include <unordered_map>
#include <functional>

#include "interface_data.hpp"

#include <boost/any.hpp>

namespace ads_interface
{

    template<typename T>
    class DataContainer
    {

        public:

        DataContainer(
            const std::string& container_name
        );

        ~DataContainer();

        bool addData(const std::string& data_name, Data<T>* data, bool override = false);

        // Removes the Data variable from the map
        // If delete_data = true, destroys the Data object as well
        bool removeData(const std::string& data_name, bool delete_data = false);

        inline std::size_t size() const
        {
            return m_DataMap.size();
        }

        private:

        std::string m_ContainerName;
        
        // TODO: Change boost::any to Data<T>
        std::unordered_map<std::string, Data<T>*> m_DataMap;     

    };

    template<typename T>
    DataContainer<T>::DataContainer(
        const std::string& container_name
    ) : m_ContainerName(container_name)
    {

    }

    template<typename T>
    DataContainer<T>::~DataContainer()
    {

    }

    template<typename T>
    bool DataContainer<T>::addData(const std::string& data_name, Data<T>* data, bool override)
    {
        if(m_DataMap.find(data_name) != m_DataMap.end() && !override)
        {
            std::cout << "Key already exists. Set override to true if you want to delete the current variable and assign another in its -place" << std::endl;

            return false;
        }
        else if(m_DataMap.find(data_name) != m_DataMap.end() && override)
        {
            removeData(data_name);

            m_DataMap[data_name] = data;

            return true;
        }

        m_DataMap[data_name] = data;

        return true;
    }

    template<typename T>
    bool DataContainer<T>::removeData(const std::string& data_name, bool delete_data)
    {
        if(m_DataMap.find(data_name) == m_DataMap.end())
        {
            std::cout << "Key does not exist in the data map." << std::endl;

            return false;
        }

        if(delete_data)
        {

            auto key = m_DataMap.find(data_name);
            
            m_DataMap.erase(data_name);
            return true;
        }

        m_DataMap.erase(data_name);

        return true;

    }

}

#endif