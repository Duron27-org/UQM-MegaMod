# MegaMod ReadMe

Send any bug reports or issues to: https://github.com/JHGuitarFreak/UQM-MegaMod/issues

First, a note on mod compatibility

MegaMod is not compatible with any other mods nor are they compatible with MegaMod.
MegaMod is completely independant from Core UQM, HD-Mod, HD-Remix, Crazy Mod, Balance Mod, Extended, or any other mods.
As such MegaMod has its own set of packages and add-ons.

For example the HD-Mod add-on package `hires4x.zip` is not compatible with MegaMod as MegaMod has its own HD package currently named `mm-0.8.2-hd.uqm`.

And as MegaMod is not compatible with any other mods, do not install it over any existing UQM installations.

All current MegaMod compatible add-ons and content can be found on the main website's Releases page: https://uqm-mods.sourceforge.net/Releases

Explanation of the Setup Menu options:

# Graphics
  
      Graphics - Toggles between original and HD graphics.

      Resolution - Scales the graphics of Original and HD graphics to the selected resolution.
                    Disclaimer: When switching to HD graphics for the first time make sure to choose 'Default' resolution.

      Custom Resolution - A text entry field that lets you input a custom resolution

      Display Mode - Choose between windowed, exclusive fullscreen (changes the display resolution to fit game resolution), or borderless full screen (stretches the game to the display resolution [SDL2 only])

      Gamma Correction - Adjusts the gamma of the screen.

# PC / 3DO

      Platform UI - Choose between DOS, 3DO, or UQM to change the UI scaling to match your option of choice. 
                    DOS has an aspect ratio 16:10 (320x200/1280x800) and form fits the UI to look just like the DOS version
                    3DO has an aspect ratio of 4:3 and adds padding to all sides and compensates the viewing area to match the look and feel of the 3DO version
                    UQM uses the full 4:3 aspect ratio just like vanilla UQM

      Melee Zoom - For Android the Melee Zoom option has been 'enhanced' to allow the user to choose which melee scaler to improve game speed. The choices are between Step, Nearest, Bilinear, and Trilinear.
                    The lowest option is a step zoom and will be the fastest on all devices. The 'Nearest' scaler will be the fastest for Smooth Scaling melee. Your mileage may vary depending on your device.

      Flagship Engine Color - Switch between the Green (PC) variant or Red (3DO) variant engined Flagship.

      Screen Transitions - This option allows the user to switch between Stepped zooming and Crossfade for various screen transitions. Stepped is the method used in the origina PC version of SC2.
                            While Crossfade is what is used in the 3DO version of SC2. There is no performance difference between the two although the Stepped method has instantaneous transition.

      Oscilloscope Style - Choose between PC or 3DO oscilloscope display during conversations

      Planet Style - This option allows the user to choose between either PC or 3DO styled planets. PC planets seem to have more contrast and color than the 3DO planets. 
                      Only works when Textured Planets is disabled.

      Star Background - This option lets you choose between PC, 3DO, UQM, or HD-mod star backgrounds in interplanetary.
                         Only functional when not using a Custom Seed.

      Stats Display - Choose scan stats style between DOS text, 3DO pictograms, Project 6014 styled DOS text, or Project 6014 styled 3DO pictograms.

      Scanning Style - Choose between PC style static scan where nodes pop up seemingly at random or 3DO style which sweeps down the planet map revealing nodes in order.

      Sphere Style - Choose between DOS, 3DO, or UQM styled planet spheres on the scan screen.

      Sphere Scan Overlay - Choose to have the spinning sphere shown during scan to be colored or plain.

      Lander View Style - Choose between PC or 3DO lander views. For PC the lander viewport is at the bottom-right of the screen with the lander details to the left of the planet map.
                          For 3DO the lander viewport is above the planet map with the lander details at the bottom-right of the screen.

# Visuals

      Date Format - Allows you to choose between popular date formats for the date display in-game.

      Custom Border - Enables a custom UI overlay based on Clay's "sc2redo" mock-up.

      Show Whole Fuel Value - When enabled shows you the full fuel value in decimal format.

      Fuel Range Indicators - Choose between default fuel range, an extra dotted circle that shows fuel range at the destination, an extra ellipse that depicts the point of no return from Sol, or all fuel range indicators at once.

      HD Animations - HD-only: Enables animated HD-mod HyperSpace stars, gravity wells, Hyper/QuasiSpace portals, and solar system suns.

      Alternate Orz Font - Turn on/off the alternate font for untranslated Orz text.

      Non-Stop Oscilloscope - Enable the conversation oscilloscope to switch to music when nobody is talking (When speech is enabled).

      Show Nebulae - Shows pre-rendered nebulae on the background of solar systems and the encounter screen when enabled.

      Nebulae Brightness - A slider that adjusts the opacity of the pre-rendered nebulae.

      Orbiting Planets - Planets/moons will orbit around their respective parental body.

      Textured Planets - Planets/moons will be fully textured in solar system view so you can identify what they are before scanning.

      Unscaled View - HD-only: Orbit lines and background stars aren't scaled up.

      NPC Ship Orientation - Turn on/off whether NPC ships face their direction of travel.

      Hazard Colors - Enables colored text on the scan screen based on the severity of the hazard

      Planet Map Textures - Switch between 3DO or UQM planet textures and node locations (minerals and bios). Added bonus when set to 3DO is that the node locations are identical to the PC version as well. Only when using the default custom seed (16807).
      
# Music

      Volasaurus' Remixes - Toggles on or off remixes made by Volasaurus. Only applicable if you have the package installed.

      Interplanetary Alien Ambience - This option enables music that plays when you are in the orbit of a star within an alien race's Sphere of Influence.

      Music Resume - Resumes music from where it last left off.
                    5 Minutes option keeps tabs on each piece of music and resets it to the beginning if it hasn't been active within 5 minutes.
                    Indefinite resumes the music no matter when it last was heard.

# Controls

      Control Display - Change the on-screen control display between Keyboard, Xbox, or Playstation 4 controls.
                        Make sure that when you choose Xbox or PS4 display to change the Bottom Player layout accordingly.

# Advanced - Spoilers for the different modes will be at the bottom of the page

      Difficulty - Toggles between Normal, Easy, and Hard difficulties with a 4th option to pick difficulty when starting a new game.

      Extended Lore - Enables extra lore provided by 0xDEC0DE's UQM-Extended mod plus a few suggested by Tarp from the Alliance Discord server.

      Nomad Mode - Enables a survival version of the gameplay where you do not have access to the Earth Starbase.

      Slaughter Mode - Enabled the ability to affect select alien race's Sphere of Influence by destroying their ships in battle.
                        WARNING: Affected SOI perists in saved games even when disabled.

      Custom Seed - A text input option that allows you to change the universe seed. Changing the seed generates new star patterns, planet order, planet type, and number of planets where applicable,
                    moon type, number of moons, and Quasispace portal exits. Planets and moons included in 'spoken' lore do not change order but can be different types that are similar to their original type.
      
      Skip Intro - Skips the logo screen, game intro, and if you have the 3DO videos installed it skips the "attract" Crystal Dynamics video.

      Partial Pickup - Minerals that are bigger than the remaining limit of the Lander's hold will be partially picked up, leaving the rest on the planet surface.
                        Also Biological data will not be picked up if the data is larger than the remaining limit of the Lander's hold.

      Game Over Cutscenes - Enables/disables game over cutscenes

      In-Game Help Menus - Enables/disables on-screen helpers for mineral worth while landing and StarMap keys while on the StarMap

      Smart Auto-Pilot - Enables Auto-Pilot to find the shortest distance outside of the current solar system. Also shows Auto-Pilot destination and distance to destination.

      Advanced Auto-Pilot - Finds the cheapest route (fuel-wise) through HyperSpace or QuasiSpace and pilots the ship for you on that route.

      Show Visited Stars - When enabled stars that you have visited will be dimmed Varyand their names will be encapsulated by parenthesis.

      Super-Melee Ship Descriptions - Show Star Control 1-styled short ship descriptions at the bottom of the main Super-Melee menu while picking a ship for your fleet.

# Cheats
    
      Kohr-Stahp - When enabled this option stops the Kohr-Ah from moving during the Death March event.

      Kohr-Ah DeCleansing - When enabled this option pushes the Death March 100 years into the future.
                            Does not work if the Death March is in progress, use Kohr-Stahp or Time Dilation as an alternative.

      God Modes - 4 options with varying degrees of "God Mode". 
                      1. Disabled
                      2. Infinite weapon energy (refills instantly when weapons are fired)
                      3. No damage/Infinite health
                      4. Infinite weapon energy & no damage/infinite health
                      Does not work against non-AI opponents.

      Time Dilation - Speeds up or slows down the flow of time. The slow option makes time move 6 times slower while the fast option moves time 5 times faster.

      Bubble Warp - Instantaneously travel to any point on the StarMap if you have enough fuel.

      Head Start - Gives you one radioactive, the Moon base in your devices, and Fwiffo in your fleet to start the game quickly.

      Unlock Ships - While enabled this option gives you the ability to build any ship in the ShipYard.

      Unlock Upgrades - Permanently gives you all Melnorme tech upgrades.

      Infinite R.U. - While enabled you will have infinite Resource Units.

      Infinite Fuel - While enabled you will have infinite fuel.

      Add All Devices - Permanently gives you every device.

      No HyperSpace Encounters - Does what it says on the tin, when enabled you will encounter nobody in HyperSpace.

      No Melee Obstacles - When enabled this option removes the planet and asteroids in Super Melee. Local play only.




WARNING: SPOILERS AHEAD
WARNING: SPOILERS AHEAD
WARNING: SPOILERS AHEAD




# List of changes for the various modes

                      # Hard Mode
                        - Keep time running while orbiting a planet & during a landing excursion
                        - Allow VUX to warp in close in Melee for the main game
                        - The Kohr-Ah Death March happens one year earlier
                        - Melnorme tech will increase in price as you buy more
                        - All Spathi escorts flee when they slave shield themselves
                        - Starting crew is 31 to account for the epilogue story
                        - Amount of Thraddash to defeat is 30 to become allied
                        - Crew Cost is minimally reduced when the Shofixti are revived
                        - Slylandro Probes dodge projectiles
                        - Mineral worth for Exotics is brought down to 16
                        - Slylandro Probes will orbit Rainbow Worlds, their numbers increase if left unchecked and will eventually vanish once you complete their quest
                        - New game will have a random custom seed if the set, loaded, or commandline seed isn't the default.
                        - Rainbow World and Bio credit value cut in half
                        - Weapon slots 2 & 3 take double energy
                        - Auto tracking costs double energy
                        - Evil Ones are now more dangerous, they can move and take 5 shots to can them. They are also worth 5 bio-units.
                        - Melnorme tech catalog spread out between the 9 Supergiants (No tech upgrades in Hyperspace)
                        - Reduced viability of the Druuge/Melnorme fuel exploit
                        - If player kills Tanaka they do not get a second chance with Katana
                        - Portal Spawner costs 20 whole units of fuel
                        - Selling more than 10 crew to the Druuge guarantees a price hike in crew cost and the immediate disapproval of the Commander
                        - Can only build two of any ship
                        - Tanaka's Scout only has the glory device disabled
                        - Limit the amount of crew one can buy, in total, to 1900 and lock the player out of buying crew until they revive the Shofixti (with graphical counter in the ShipYard)
                        - Harder encounters at the Chmmr homeworld, Sun Device, Aqua Helix, Ur-Quan wreck, and Syreen vault
                        - Druuge sell the Rosy Sphere on second deal
                        - No help before the final battle if the Pkunk are absorbed before triggering the Yehat rebellion
                        - Make the Sa-Matra battle more difficult
                        - Cut reinforcements in half where applicable

                      # Easy Mode
                        - The Kohr-Ah Death March is delayed by two years
                        - Double mineral worth
                        - Fwiffo starts with a full crew compliment
                        - Amount of Thraddash to defeat is 15 to become allied
                        - Tune down the battle difficulty to Weak Cyborg
                        - Start with two landers
                        - Rainbow World credit value doubled
                        - Add a couple more fusion thrusters and turning jets for new game
                        - Keep the Emergency Escape Warp Unit enabled after Chmmr Bomb installation
                        - Portal Spawner costs 5 whole units of fuel
                        - Player starts with 43.38 units of fuel (The difference between a full tank and the amount of fuel it takes to travel from Vela to Sol)
                        - Player starts with an extra 2500 R.U.
                        - Limit to the amount of crew to sell to the Druuge before crew cost hike is 200
                        - Commander will tell you about the Melnorme and ZFP earlier than usual

                      # Extended Lore
                        - Apply unused Melnorme dialog when filling tanks to their full capacity
                        - The Ur-Quan's Talking Pet now uses an alternate color palette
                        - The Kzer-Za have their classic baton back on comm screens
                        - Admiral ZEX has an alternate uniform and more medals, differing him from other VUX
                        - Added small chance of weather and tectonic hazards to level 2
                        - Ships exploding in Super Melee do not lose all velocity
                        - Added ability to open up a HyperSpace portal in QuasiSpace to go right back to where you opened up the initial QuasiSpace portal
                        - The Kohr-Ah lose a tiny fraction of their SOI when the Supox and Utwig attack them.
                        - The Melnorme will now disappear once the Death March starts
                        - The Kohr-Ah will now respond to HyperSpace broadcasts during their Death March
                        - Show the Sa-Matra as a planet on the penultimate battle screen
                        - Use the Sa-Matra as a planet for the penultimate battle
                        - Talk to Kohr-Ah when at the Sa-Matra during Death March
                        - Allies will not chase you if you get close to their ships
                        - No longer possible to encounter random Ur-Quan ships in the Zoq-Fot-Pik home system, like their dialogs say (Bugzilla Bug #759)
                        - Add a "dead" slave-shielded world and starbase in Gamma Ophiuchi (033.3 : 091.6)
                        - Destroyed Ur-Quan(*) / Kohr-Ah(+) starbases
                          + Beta Reticuli (702.0 : 529.1)
                          * Metis (570.8 : 460.4)
                          * Gamma Cancri (500.6 : 501.1)
                          * Alpha Lentilis (462.5 : 600.0)
                          + Theta Chamaeleonis (514.5 : 695.8)
                          + Antares (647.9 : 754.1)
                        - The Syreen will have a Sphere of Influence at the completion of their Vault Quest
                        - The Chmmr will have a Sphere of Influence once you help them complete their Process
                        - Defunct Mother-Ark @ Delta Virginis IV
                        - Stripped Precursor Starbase @ Alpha Centauri
                        - Ruins and lore on Algol IV to match with the lore as told by the Melnorme
                        - Add a Spathi erected monument to the peaceful negotiatons of colonization between them and the Mmrnmhrm on Beta Herculis II
                        - The Thraddash will survive the Ilwrath war if you are allied with them. And they will let you take the AquaHelix peacefully
                        - Starting crew is 31 to account for the epilogue story
                        - New Androsynth excavation site on Alpha Lalande 1
                        - Show gas giant type on the scan screen (I.E. Blue Gas Giant)
                        - Charon, the moon of Pluto, is now explorable
                        - Charon generates previously unused element "Charon Dust"
                        - Unzervalt now has a single moon as per the intro artwork
                        - Show Sa-Matra in background during penultimate battle
                        - Set Zex's Beauty free upon the planet after it devours Zex
                        - Ability to fill Syreen crew to max in the Shipyard
                        - New Precursor artifact on Alpha Apodis 4
                        - Added the ability to tell the Ilwrath to GTFO of any star system in their SOI via Hyperwave Broadcaster a maximum of 5 times before they wise-up and attack you
                        - Made Beta Arae (933.3:093.7) an Orange Super Giant (Because there are no Orange Super Giants normally)
                        - "Pop" Gamma Ophiuchi's slave shield on Arilou destruction
                        - "Pop" Spathiwa's slave shield and generate 3-4 ruins on Orz destruction
                        - Gave the Chmmr and Syreen ruined planets and StarBases when "cleansed"

                      # Nomad Mode
                        - New message report for the Earth Starbase when you try to dock
                        - Player will no longer "pick up" the base on Luna
                        - Emergency Warp Unit activated without needing to visit the Starbase
                        - Add a starbase around Kyabetsu that will give the player a max of two Scouts at a time after their quest is completed
                        - Give player two extra jets and thrusters so as to not be completely outmatched in speed
                        - Make Probes spawn at a reasonable rate so as to not annoy the player
                        - When allied, Spathi ships can join your fleet when asked for a max of 3 ships in your fleet at a time.
                        - Player starts with 20 more units of fuel