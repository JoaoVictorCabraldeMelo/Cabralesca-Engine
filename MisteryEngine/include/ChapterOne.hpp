#ifndef _CHAPTER_ONE_H_
#define _CHAPTER_ONE_H_

#include "State.hpp"

class ChapterOne : public State {
  public:
    ChapterOne();

    ~ChapterOne();

    void LoadAssets() override;

    void Update(float dt) override;

    void Render() override;

    void Start() override;

    void Pause() override;

    void Resume() override;
};

#endif