#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QSoundEffect>
#include <QMap>
#include <QString>

class SoundManager : public QObject {
    Q_OBJECT
public:
    SoundManager(QObject *parent = nullptr) : QObject(parent) {
        // Initialize each sound effect with a file path
        loadSound("move_self", ":/sound_effects/soundEffects/move-self.wav");
        loadSound("move_opponent", ":/sound_effects/soundEffects/move-opponent.wav");
        loadSound("capture", ":/sound_effects/soundEffects/capture.wav");
        loadSound("check", ":/sound_effects/soundEffects/move-check.wav");
        loadSound("castle", ":/sound_effects/soundEffects/castle.wav");
        loadSound("game_end", ":/sound_effects/soundEffects/game-end.wav");
        loadSound("game_start", ":/sound_effects/soundEffects/game-start.wav");
        loadSound("illegal", ":/sound_effects/soundEffects/illegal.wav");
        loadSound("promote", ":/sound_effects/soundEffects/promote.wav");
    }

    ~SoundManager() {
        // Clean up the sound effects
        for (auto effect : soundEffects) {
            delete effect;
            effect = nullptr;
        }
    }
    void check() {playSound("check");}
    void move_self() {playSound("move_self");}
    void move_opponent() {playSound("move_opponent");}
    void capture() {playSound("capture");}
    void castle() {playSound("castle");}
    void game_end() {playSound("game_end");}
    void game_start() {playSound("game_start");}
    void illegal() {playSound("illegal");}
    void promote() {playSound("promote");}
private:
    QMap<QString, QSoundEffect*> soundEffects;

    void loadSound(const QString &name, const QString &filePath) {
        QSoundEffect *soundEffect = new QSoundEffect(this);
        soundEffect->setSource(QUrl::fromLocalFile(filePath));
        soundEffect->setVolume(0.5);  // Adjust volume if needed
        soundEffect->setLoopCount(1);
        soundEffects[name] = soundEffect;
    }
    void playSound(const QString &soundName) {
        if (soundEffects.contains(soundName)) {
            soundEffects[soundName]->play();
        }
    }
};
#endif // SOUNDMANAGER_H
