#include "GameWorld.h"
#include "GameObjects.h"
#include "utils.h"
#include <sstream>
#include <cmath>
GameWorld::GameWorld() : m_dawnbreaker(nullptr), m_gameObjects(), m_lives(3) {

}

GameWorld::~GameWorld() {}

void GameWorld::Init() { 
  m_dawnbreaker = new Dawnbreaker(300, 100, this);
  m_gameObjects.push_back(m_dawnbreaker);

  for (int i = 0; i < 30; i++) {
    m_gameObjects.push_back(new Star(randInt(0, WINDOW_WIDTH), randInt(0, WINDOW_HEIGHT - 1), randInt(10, 40) / 100.0, this));
  }
}

LevelStatus GameWorld::Update() {
  if (randInt(1, 30) == 1) {
      m_gameObjects.push_back(new Star(randInt(0, WINDOW_WIDTH), WINDOW_HEIGHT - 1, randInt(10, 40) / 100.0, this));
  }

  for (auto& gameObject : m_gameObjects) {
    gameObject->Update();
  }

  if (!GetDawnbreaker()->IsAlive()) {
    m_lives--;
    return LevelStatus::DAWNBREAKER_DESTROYED;
  }
  //检测关卡是否胜利（是否已经消灭了(3 * level)架敌机），若胜利则前进一关，并返回LevelStatus::LEVEL_CLEARED。
  if (m_gameObjects.size() == 0) {
    return LevelStatus::LEVEL_CLEARED;
  }
  auto iter = m_gameObjects.begin();
  while (iter != m_gameObjects.end()) {
    if (!(*iter)->IsAlive()) {
      delete (*iter);
      iter = m_gameObjects.erase(iter);
    }
    else {
      ++iter;
    }
  }
  /*根据破晓号的状态和关卡状态，显示底部的状态栏。你可以使用GameWorld 中的
SetStatusBarMessage()函数。 
 需要显示的内容为：（以下X 代表一个整数，每两项之间需要有3 个空格） HP: X/100   Meteors: X   Lives: X   Level: X   Enemies: X/X   Score: X */
  std::stringstream ss;
  ss << "HP: " << GetDawnbreaker()->GetHP() << "/100   Meteors: " << m_gameObjects.size() << "   Lives: " << m_lives << "   Level: " << m_level << "   Enemies: " << m_gameObjects.size() << "/" << m_level * 3 << "   Score: " << m_score;
  SetStatusBarMessage(ss.str()); 
  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
  m_dawnbreaker = nullptr;

  auto iter = m_gameObjects.begin();
  while (iter != m_gameObjects.end()) {
    delete (*iter);
    iter = m_gameObjects.erase(iter);
  }
}

bool GameWorld::IsGameOver() const{
  return m_lives <= 0;
}

void GameWorld::Instantiate(GameObject* newGameObject) {
  m_gameObjects.push_back(newGameObject);
}

Dawnbreaker* GameWorld::GetDawnbreaker() const {
  return m_dawnbreaker;
}