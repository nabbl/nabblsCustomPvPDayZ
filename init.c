
void main()
{

	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	Weather weather = g_Game.GetWeather();

	weather.GetOvercast().SetLimits( 0.0 , 1.0 );
	weather.GetRain().SetLimits( 0.0 , 1.0 );
	weather.GetFog().SetLimits( 0.0 , 0.25 );

	weather.GetOvercast().SetForecastChangeLimits( 0.0, 0.2 );
	weather.GetRain().SetForecastChangeLimits( 0.0, 0.1 );
	weather.GetFog().SetForecastChangeLimits( 0.15, 0.45 );

	weather.GetOvercast().SetForecastTimeLimits( 1800 , 1800 );
	weather.GetRain().SetForecastTimeLimits( 600 , 600 );
	weather.GetFog().SetForecastTimeLimits( 1800 , 1800 );

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.0, 0.3), 0, 0);
	weather.GetRain().Set( Math.RandomFloatInclusive(0.0, 0.2), 0, 0);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.0, 0.1), 0, 0);
	
	weather.SetWindMaximumSpeed(15);
	weather.SetWindFunctionParams(0.1, 0.3, 50);
}

class CustomMission: MissionServer
{

  override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
		Class.CastTo(m_player, playerEnt);

		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

	void addMags(string mag_type, int count) {
		for (int i = 0; i < count; i++) {
			EntityAI mag = m_player.GetInventory().CreateInInventory(mag_type);
      m_player.SetQuickBarEntityShortcut(mag, i+1, true);
		}
	}

	EntityAI m4Class() {
    EntityAI gun = m_player.GetHumanInventory().CreateInHands("M4A1");
    gun.GetInventory().CreateAttachment("M4_PlasticHndgrd");
    gun.GetInventory().CreateAttachment("M4_OEBttstck");
		gun.GetInventory().CreateAttachment("ACOGOptic");
    // EntityAI ent_mag = m_player.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
    // Weapon_Base wpn;
    // Magazine mag;
    // Class.CastTo( wpn,  gun);
    // Class.CastTo( mag,  ent_mag );
    // if(m_player.GetWeaponManager().CanAttachMagazine( wpn, mag ) ) {
    //   Print("WE WANT TO ATTACH MAGAZINE");
    //   m_player.GetWeaponManager().AttachMagazine( mag );
    // }
    addMags("Mag_STANAG_30Rnd", 4)
    Print("WE SPAWN WITH ASSAULT CLASS");
		return gun;
	}

  EntityAI akmClass() {
    EntityAI gun = m_player.GetHumanInventory().CreateInHands("AKM");
    gun.GetInventory().CreateAttachment( "AK_WoodBttstck" );
    gun.GetInventory().CreateAttachment( "AK_WoodHndgrd" );
    gun.GetInventory().CreateAttachment( "KobraOptic" );
    // gun.GetInventory().CreateAttachment( "PSO1Optic" );
    addMags("Mag_AKM_30Rnd", 4)

		return gun;
	}

	EntityAI sniperClass() {
		EntityAI gun = m_player.GetHumanInventory().CreateInHands("SVD");
		gun.GetInventory().CreateAttachment("PSO1Optic");
		addMags("Mag_SVD_10Rnd", 4);

		return gun;
	}

	EntityAI smgClass() {
		EntityAI gun = m_player.GetHumanInventory().CreateInHands("UMP45");
		gun.GetInventory().CreateAttachment("PistolSuppressor");
		addMags("Mag_UMP_25Rnd", 4);

		return gun;
	}

  override void OnClientRespawnEvent(PlayerIdentity identity, PlayerBase player) // Create new character when logging in to server
  {
      player.SetHealth("", "", 0.0);
      Print("OnClientRespawnEvent");
  }
  override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
  {
      if(player) {player.SetHealth("", "", 0.0);}
      super.PlayerDisconnected(player, identity, uid);
  }
  override void OnClientReadyEvent(PlayerIdentity identity, PlayerBase player)
  {
      GetGame().SelectPlayer(identity, player);
  }

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
    TStringArray Bags, Hands, Tops, Vests, Pants, Shoes, HeadThings, weapchoices;
    HeadThings = {"BallisticHelmet_Black", "BallisticHelmet_Green", "BallisticHelmet_UN", "BoonieHat_DPM", "BoonieHat_DPM", "WolfMask"};
    Tops = {"MiniDress_Pink","Raincoat_Pink","MiniDress_Pink","M65Jacket_Olive","TTsKOJacket_Camo","GorkaEJacket_Summer","GorkaEJacket_Flat","GorkaEJacket_Autumn","GorkaEJacket_PautRev","RidersJacket_Black"};
    Vests = {"PlateCarrierComplete","HighCapacityVest_Olive","HighCapacityVest_Black"};
    Pants = {"GorkaPants_PautRev","GorkaPants_Flat","GorkaPants_Autumn","GorkaPants_Summer","CargoPants_Blue","CargoPants_Beige","CargoPants_Black","CargoPants_Green","CargoPants_Grey","TTSKOPants","HunterPants_Autumn","HunterPants_Brown","HunterPants_Spring","HunterPants_Summer","HunterPants_Winter"};
    weapchoices = {"AKM", "M4", "SVD", "UMP", "MP5"}
    
    m_player.SetBloodyHands(true);
    m_player.SetHealth( m_player.GetMaxHealth( "", "" ) );
    m_player.SetHealth( "","Blood", m_player.GetMaxHealth( "", "Blood" ) );
    m_player.GetStatStamina().Set(1000);
    m_player.GetStatEnergy().Set(1000);
    m_player.GetStatWater().Set(1000);
    m_player.GetStatStomachSolid().Set(300);
    m_player.GetStatStomachWater().Set(300);
    m_player.GetStatStomachEnergy().Set(300);
		m_player.RemoveAllItems();

    m_player.GetInventory().CreateInInventory(Tops.GetRandomElement());
    m_player.GetInventory().CreateInInventory(Pants.GetRandomElement());
    m_player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
    m_player.GetInventory().CreateInInventory(Vests.GetRandomElement());
    m_player.GetInventory().CreateInInventory(HeadThings.GetRandomElement());
            
    EntityAI rags = m_player.GetInventory().CreateInInventory("Rag");
    EntityAI battery = m_player.GetInventory().CreateInInventory("Battery9V");
		ItemBase.Cast(rags).SetQuantity(4);

		EntityAI primary;
		EntityAI axe = m_player.GetInventory().CreateInInventory("FirefighterAxe");

		switch (Math.RandomInt(0, 4)) {
			case 0: primary = m4Class(); break;
      case 1: primary = akmClass(); break;
			case 2: primary = sniperClass(); break;
			case 3: primary = smgClass(); break;
		}

		
		m_player.SetQuickBarEntityShortcut(primary, 0, true);
		m_player.SetQuickBarEntityShortcut(rags, 6, true);
		m_player.SetQuickBarEntityShortcut(axe, 7, true);
	}

	
	// override void OnUpdate( float timeslice )
	// {
  //   super.OnUpdate( timeslice );
  // }

  // override void OnKeyPress( int key )
	// {
	// 	super.OnKeyPress(key);

  // 	if (key == KeyCode.KC_R )
	// 	{
  //     Print("TRY TO RELOAD");
  //     Reload();
  //   }
  // }

  // void OnKeyPress( int key )
	// {

  //   Print("THIS WAS CALLED");
  // 	if (key == KeyCode.KC_R )
	// 	{
  //     Print("TRY TO RELOAD");
  //     Reload();
  //   }
  // }

  // void Reload()
  // {
  //   EntityAI oWeapon = m_player.GetHumanInventory().GetEntityInHands();

  //   if( oWeapon )
  //   {
  //       Magazine oMag = ( Magazine ) oWeapon.GetAttachmentByConfigTypeName( "DefaultMagazine" );

  //       if( oMag && oMag.IsMagazine() )
  //       {
  //         Print("TRY TO SET AMMO TO MAX");
  //           oMag.LocalSetAmmoMax();
  //       }

  //       Object oSupressor = ( Object ) oWeapon.GetAttachmentByConfigTypeName( "SuppressorBase" );

  //       if( oSupressor )
  //       {
  //           oSupressor.SetHealth( oSupressor.GetMaxHealth( "", "" ) );
  //       }
  //   }
  // }
	
};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
