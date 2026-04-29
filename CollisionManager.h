#pragma once

#include <vector>

#include "Collider.h" 

class CollisionManager 
{
    bool neverDie = false;
public:

    // Initialize And Assign Functions That Will Be Called During Collision
    void Init(void (*_OnCollisionWithObstacle)(), void (*_OnCollisionWithStar)(), void (*_OnCollisionWithStar2)(), void (*_OnCollisionWithStar3)())
    {
        OnCollisionWithObstacle = _OnCollisionWithObstacle;
        OnCollisionWithStar = _OnCollisionWithStar;
        OnCollisionWithStar2 = _OnCollisionWithStar2;
        OnCollisionWithStar3 = _OnCollisionWithStar3;

    }

    // Add A New BoxCollider To The Collision Manager
    void AddCollider(BoxCollider* BoxCollider) {
        colliders.push_back(BoxCollider);
    }
    
    // Remove A BoxCollider From The Collision Manager
    void RemoveCollider(BoxCollider* BoxCollider) {
        auto it = std::remove(colliders.begin(), colliders.end(), BoxCollider);
        if (it != colliders.end()) {
            colliders.erase(it, colliders.end());
        }
    }

    // Check Collision Between Objects
    void CheckCollisions() {
        for (size_t i = 0; i < colliders.size(); ++i) {
            for (size_t j = i + 1; j < colliders.size(); ++j) { // Avoid self-collision
                if (colliders[i]->CheckCollision(*colliders[j])) {
                    HandleCollision(colliders[i], colliders[j]);
                }
            }
        }
    }

private:
    std::vector<BoxCollider*> colliders;  // List Of Colliders

    // Detects Collision Between Two Colliders And Calls Functions Upon Collision
    void HandleCollision(BoxCollider* colliderA, BoxCollider* colliderB) {
        if ((colliderA->tag == "Obstacle" and colliderB->tag == "Player") or (colliderA->tag == "Player" and colliderB->tag == "Obstacle"))
        {
            if (OnCollisionWithObstacle != nullptr)
            {
                if(neverDie == false)
                  OnCollisionWithObstacle();

            }
        }

        if ((colliderA->tag == "Star" and colliderB->tag == "Player") or (colliderA->tag == "Player" and colliderB->tag == "Star"))
        {
            if (OnCollisionWithStar != nullptr)
            {
                OnCollisionWithStar();
            }
        }
        if ((colliderA->tag == "Star2" and colliderB->tag == "Player") or (colliderA->tag == "Player" and colliderB->tag == "Star2"))
        {
            if (OnCollisionWithStar2 != nullptr)
            {
                OnCollisionWithStar2();
            }
        }
        if ((colliderA->tag == "Star3" and colliderB->tag == "Player") or (colliderA->tag == "Player" and colliderB->tag == "Star3"))
        {
            if (OnCollisionWithStar3 != nullptr)
            {
                OnCollisionWithStar3();
            }
        }
    }

    // Function Pointers
    void (*OnCollisionWithObstacle)();
    void (*OnCollisionWithStar)();
    void (*OnCollisionWithStar2)();
    void (*OnCollisionWithStar3)();
  
};



