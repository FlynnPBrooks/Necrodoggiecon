#pragma once
#include "CEntity.h"
class CT_EditorEntity :
    public CEntity
{
protected:

   // class CSpriteComponent* sprite = nullptr;

    int EntitySlotID;


public:

    class CSpriteComponent* sprite = nullptr;

    CT_EditorEntity();

    virtual void Update(float deltaTime) override;


    virtual void InitialiseEntity(int SlotID);

    virtual void SaveEntity();




};

class CT_Editor_ItemHolder :
    public CT_EditorEntity
{
protected:

    // class CSpriteComponent* sprite = nullptr;

 

    int ItemSlot;
public:



    CT_Editor_ItemHolder();

    virtual void Update(float deltaTime) override;


  

    virtual void InitialiseEntity(int SlotID);



};

class CT_EditorEntity_Enemy :
    public CT_EditorEntity
{
protected:

    // class CSpriteComponent* sprite = nullptr;

  
public:
    int CharacterSlot;

    std::vector<Vector2> Waypoints;


    CT_EditorEntity_Enemy();

    virtual void Update(float deltaTime) override;


    virtual void InitialiseEntity(int SlotID);

    virtual void SaveEntity();

    





};


