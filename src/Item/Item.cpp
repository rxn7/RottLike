#include "Item.hpp"
#include "PlayerBase.hpp"

Item::Item(){

}

Item::~Item(){

}

Item::Item(ITEM_CTOR_PARAMS) : mp_holder(p_holder) {
}

void Item::setHolder(ITEM_CTOR_PARAMS){
    mp_holder = p_holder;
}

PlayerBase* Item::getHolder(){
    return mp_holder;
}

bool Item::isHeldByLocalPlayer() const {
    return mp_holder->isLocal();
}