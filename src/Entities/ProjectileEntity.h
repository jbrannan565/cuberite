
// ProjectileEntity.h

// Declares the cProjectileEntity class representing the common base class for projectiles, as well as individual projectile types





#pragma once

#include "Entity.h"





// tolua_begin

class cProjectileEntity :
	public cEntity
{
	typedef cEntity super;
	
public:
	/// The kind of the projectile. The numbers correspond to the network type ID used for spawning via the 0x17 packet.
	enum eKind
	{
		pkArrow         = 60,
		pkSnowball      = 61,
		pkEgg           = 62,
		pkGhastFireball = 63,
		pkFireCharge    = 64,
		pkEnderPearl    = 65,
		pkExpBottle     = 75,
		pkSplashPotion  = 73,
		pkFirework      = 76,
		pkWitherSkull   = 66,
		pkFishingFloat  = 90,
	} ;
	
	// tolua_end
	
	CLASS_PROTODEF(cProjectileEntity);

	cProjectileEntity(eKind a_Kind, cEntity * a_Creator, double a_X, double a_Y, double a_Z, double a_Width, double a_Height);
	cProjectileEntity(eKind a_Kind, cEntity * a_Creator, const Vector3d & a_Pos, const Vector3d & a_Speed, double a_Width, double a_Height);
	
	static cProjectileEntity * Create(eKind a_Kind, cEntity * a_Creator, double a_X, double a_Y, double a_Z, const cItem & a_Item, const Vector3d * a_Speed = NULL);
	
	/// Called by the physics blocktracer when the entity hits a solid block, the hit position and the face hit (BLOCK_FACE_) is given
	virtual void OnHitSolidBlock(const Vector3d & a_HitPos, eBlockFace a_HitFace);
	
	/// Called by the physics blocktracer when the entity hits another entity
	virtual void OnHitEntity(cEntity & a_EntityHit, const Vector3d & a_HitPos) 
	{
		UNUSED(a_EntityHit);
		UNUSED(a_HitPos);
	}
	
	/// Called by Chunk when the projectile is eligible for player collection
	virtual void CollectedBy(cPlayer * a_Dest);

	// tolua_begin

	/// Returns the kind of the projectile (fast class identification)
	eKind GetProjectileKind(void) const { return m_ProjectileKind; }
	
	/// Returns the entity who created this projectile; may be NULL
	cEntity * GetCreator(void) { return m_Creator; }
	
	/// Returns the string that is used as the entity type (class name) in MCA files
	AString GetMCAClassName(void) const;
	
	/// Returns true if the projectile has hit the ground and is stuck there
	bool IsInGround(void) const { return m_IsInGround; }
	
	// tolua_end
	
	/// Sets the internal InGround flag. To be used by MCA loader only!
	void SetIsInGround(bool a_IsInGround) { m_IsInGround = a_IsInGround; }
	
protected:
	eKind m_ProjectileKind;
	
	/// The entity who has created this projectile; may be NULL (e. g. for dispensers)
	cEntity * m_Creator;
	
	/// True if the projectile has hit the ground and is stuck there
	bool m_IsInGround;
		
	// cEntity overrides:
	virtual void Tick(float a_Dt, cChunk & a_Chunk) override;
	virtual void HandlePhysics(float a_Dt, cChunk & a_Chunk) override;
	virtual void SpawnOn(cClientHandle & a_Client) override;
	
	// tolua_begin
} ;





class cThrownEggEntity :
	public cProjectileEntity
{
	typedef cProjectileEntity super;
	
public:

	// tolua_end
	
	CLASS_PROTODEF(cThrownEggEntity);

	cThrownEggEntity(cEntity * a_Creator, double a_X, double a_Y, double a_Z, const Vector3d & a_Speed);
	
protected:

	// tolua_end
	
	// cProjectileEntity overrides:
	virtual void OnHitSolidBlock(const Vector3d & a_HitPos, eBlockFace a_HitFace) override;
	virtual void OnHitEntity    (cEntity & a_EntityHit, const Vector3d & a_HitPos) override;
	
	// Randomly decides whether to spawn a chicken where the egg lands.
	void TrySpawnChicken(const Vector3d & a_HitPos);
	
	// tolua_begin
	
} ;





class cThrownEnderPearlEntity :
	public cProjectileEntity
{
	typedef cProjectileEntity super;
	
public:

	// tolua_end
	
	CLASS_PROTODEF(cThrownEnderPearlEntity);

	cThrownEnderPearlEntity(cEntity * a_Creator, double a_X, double a_Y, double a_Z, const Vector3d & a_Speed);
	
protected:

	// tolua_end
	
	// cProjectileEntity overrides:
	virtual void OnHitSolidBlock(const Vector3d & a_HitPos, eBlockFace a_HitFace) override;
	virtual void OnHitEntity    (cEntity & a_EntityHit, const Vector3d & a_HitPos) override;
	
	// Teleports the creator where the ender pearl lands.
	void TeleportCreator(const Vector3d & a_HitPos);

	// tolua_begin
	
} ;





class cThrownSnowballEntity :
	public cProjectileEntity
{
	typedef cProjectileEntity super;
	
public:

	// tolua_end
	
	CLASS_PROTODEF(cThrownSnowballEntity);

	cThrownSnowballEntity(cEntity * a_Creator, double a_X, double a_Y, double a_Z, const Vector3d & a_Speed);
	
protected:
	
	// cProjectileEntity overrides:
	virtual void OnHitSolidBlock(const Vector3d & a_HitPos, eBlockFace a_HitFace) override;
	virtual void OnHitEntity    (cEntity & a_EntityHit, const Vector3d & a_HitPos) override;

	// tolua_begin
	
} ;





class cExpBottleEntity :
	public cProjectileEntity
{
	typedef cProjectileEntity super;

public:

	// tolua_end

	CLASS_PROTODEF(cExpBottleEntity);

	cExpBottleEntity(cEntity * a_Creator, double a_X, double a_Y, double a_Z, const Vector3d & a_Speed);

protected:

	// cProjectileEntity overrides:
	virtual void OnHitSolidBlock(const Vector3d & a_HitPos, eBlockFace a_HitFace) override;

	// tolua_begin

};





class cFireworkEntity :
	public cProjectileEntity
{
	typedef cProjectileEntity super;

public:

	// tolua_end

	CLASS_PROTODEF(cFireworkEntity);

	cFireworkEntity(cEntity * a_Creator, double a_X, double a_Y, double a_Z, const cItem & a_Item);
	const cItem & GetItem(void) const { return m_FireworkItem; }

protected:

	// cProjectileEntity overrides:
	virtual void HandlePhysics(float a_Dt, cChunk & a_Chunk) override;
	virtual void Tick(float a_Dt, cChunk & a_Chunk) override;

private:

	int m_ExplodeTimer;
	cItem m_FireworkItem;

	// tolua_begin

};





class cGhastFireballEntity :
	public cProjectileEntity
{
	typedef cProjectileEntity super;

public:

	// tolua_end
	
	CLASS_PROTODEF(cGhastFireballEntity);
	
	cGhastFireballEntity(cEntity * a_Creator, double a_X, double a_Y, double a_Z, const Vector3d & a_Speed);
	
protected:

	void Explode(int a_BlockX, int a_BlockY, int a_BlockZ);
	
	// cProjectileEntity overrides:
	virtual void OnHitSolidBlock(const Vector3d & a_HitPos, eBlockFace a_HitFace) override;
	virtual void OnHitEntity(cEntity & a_EntityHit, const Vector3d & a_HitPos) override;

	// TODO: Deflecting the fireballs by arrow- or sword- hits
	
	// tolua_begin
	
} ;





class cFireChargeEntity :
	public cProjectileEntity
{
	typedef cProjectileEntity super;

public:

	// tolua_end
	
	CLASS_PROTODEF(cFireChargeEntity);
	
	cFireChargeEntity(cEntity * a_Creator, double a_X, double a_Y, double a_Z, const Vector3d & a_Speed);
	
protected:

	void Explode(int a_BlockX, int a_BlockY, int a_BlockZ);

	// cProjectileEntity overrides:
	virtual void OnHitSolidBlock(const Vector3d & a_HitPos, eBlockFace a_HitFace) override;
	virtual void OnHitEntity(cEntity & a_EntityHit, const Vector3d & a_HitPos) override;

	// tolua_begin
	
} ;




// tolua_end



