#include "SignalSource.h"

SignalSource* SignalSource::m_instance = nullptr;

SignalSource *SignalSource::getInstance()
{
    if (!SignalSource::m_instance) {
        SignalSource::m_instance = new SignalSource();
    }
    return SignalSource::m_instance;
}

void SignalSource::deleteInstance()
{
    if (SignalSource::m_instance) {
        delete SignalSource::m_instance;
        SignalSource::m_instance = nullptr;
    }
}