#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <algorithm>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    void forceRestart(float) {
        this->resetLevel();
    }

    void showNewBest(bool newReward, int orbs, int diamonds, bool demonKey, bool noRetry, bool noTitle) {
        bool hideOrbs = Mod::get()->getSettingValue<bool>("hide-orbs");
        bool hideDiamonds = Mod::get()->getSettingValue<bool>("hide-diamonds");
        bool hideKey = Mod::get()->getSettingValue<bool>("hide-demonkey");

        int finalOrbs = hideOrbs ? 0 : orbs;
        int finalDiamonds = hideDiamonds ? 0 : diamonds;
        bool finalKey = hideKey ? false : demonKey;
        bool finalReward = (finalOrbs > 0 || finalDiamonds > 0 || finalKey) ? newReward : false;

        PlayLayer::showNewBest(finalReward, finalOrbs, finalDiamonds, finalKey, noRetry, noTitle);

        if (!finalReward && !noRetry && GameManager::sharedState()->getGameVariable("0026")) {
            this->scheduleOnce(schedule_selector(MyPlayLayer::forceRestart), 1.1f);
        }
    }
};

class $modify(MyPauseLayer, PauseLayer) {
    void onModSettings(CCObject*) {
        geode::openSettingsPopup(Mod::get());
    }

    void customSetup() {
        PauseLayer::customSetup();

        auto sprite = CCSprite::create("button.png"_spr);
        if (!sprite) {
            sprite = CCSprite::createWithSpriteFrameName("GJ_optionsBtn02_001.png");
        }

        float targetSize = 36.0f;
        float maxSide = (std::max)(sprite->getContentSize().width, sprite->getContentSize().height);
        if (maxSide > 0) {
            sprite->setScale(targetSize / maxSide);
        }

        auto btn = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(MyPauseLayer::onModSettings)
        );
        btn->setID("no-newbest-settings-btn"_spr);

        if (auto menu = this->getChildByID("left-button-menu")) {
            menu->addChild(btn);
            menu->updateLayout();
        }
    }
};
