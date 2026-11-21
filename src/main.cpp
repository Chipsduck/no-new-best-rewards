#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(NoNewBestPlayLayer, PlayLayer) {
    void showNewBest(bool newReward, int orbs, int diamonds, bool demonKey, bool noRetry, bool noTitle) {
        auto mod = Mod::get();

        if (mod->getSettingValue<bool>("hide-orbs")) {
            orbs = 0;
        }
        if (mod->getSettingValue<bool>("hide-diamonds")) {
            diamonds = 0;
        }
        if (mod->getSettingValue<bool>("hide-demonkey")) {
            demonKey = false;
        }

        if (orbs == 0 && diamonds == 0 && !demonKey) {
            newReward = false;
        }

        PlayLayer::showNewBest(newReward, orbs, diamonds, demonKey, noRetry, noTitle);
    }
};
