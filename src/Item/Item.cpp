#include "Item.hpp"

Item::Item(){

}

Item::~Item(){

}

Item::Item(ITEM_CTOR_PARAMS) : mp_holder(p_holder), m_is_local(is_local){
}

void Item::setHolder(ITEM_CTOR_PARAMS){
    mp_holder = p_holder;
    m_is_local = is_local;
}

RottEngine::Entity* Item::getHolder(){
    return mp_holder;
}