#include "MeleeWeapon.hpp"

MeleeWeapon::MeleeWeapon() : Item() {
}

MeleeWeapon::MeleeWeapon(ITEM_CTOR_PARAMS) : Item(p_holder, is_local) {
}

MeleeWeapon::~MeleeWeapon() {

}