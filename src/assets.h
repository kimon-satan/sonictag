//
//  assets.h
//  DRSApp
//
//  Created by Chris Kiefer on 25/07/2012.
//  Copyright (c) 2012 Goldsmiths, University of London. EAVI. All rights reserved.
//

#ifndef DRSApp_assets_h
#define DRSApp_assets_h

#include <vector>
#include <map>
#include "dimensions.h"

using namespace std;

struct part {
    string filename;
    string name;
    part(){}
    part(string p, string n):filename(p), name(n){}
};

struct song {
    string title;
    string folder;
    float bpm;
    float lengthInBars;
    float beatsPerBar;
    float gain;
    vector<part> parts;
    song(){}
    song(string t, string fol, float bpm, float bpb, float len, float amp):title(t), folder(fol), bpm(bpm), beatsPerBar(bpb), lengthInBars(len), gain(amp) {}
};

struct dimension {
    string folder;
    string country;
    string name;
    vector<song> songs;
    vector<string> icons;
    string backdrop;
    dimension(){};
    dimension(string fol, string coun, string n, string back):folder(fol),country(coun),name(n), backdrop(back) {}
};

class assets {
public:
    static map<DRSDATA::dimensions, dimension> dimensions;
    static void setup() {
        dimension china("China","China","Dimension Phantasmagoria", "phantasmagoria backdrop");
        china.songs.push_back(song("The Last Mistake", "The Last Mistake", 100, 4, 16, 3.0));
        china.songs[0].parts.push_back(part("the last mistake - app Bob bass","Bass"));
        china.songs[0].parts.push_back(part("the last mistake - app Bobby Beat","Beat"));
        china.songs[0].parts.push_back(part("the last mistake - app bridge","Bridge"));
        china.songs[0].parts.push_back(part("the last mistake - app BtBox","Beat Box"));
        china.songs[0].parts.push_back(part("the last mistake - app elec","Elec"));
        china.songs[0].parts.push_back(part("the last mistake - app H Bass","H Bass"));
        china.songs[0].parts.push_back(part("the last mistake - app roll","Roll"));

        china.icons.push_back("blue-shoes");
        china.icons.push_back("Ink-Illusionist-Girl-V02_04_02");
        china.icons.push_back("Ink-Illusionist-Girl-V02_04_06");
        china.icons.push_back("Ink-Illusionist-Girl-V02_04_09");
        china.icons.push_back("Ink-Illusionist-V01_04_03");
        china.icons.push_back("Ink-Illusionist-V01_04_07");
        china.icons.push_back("Ink-Illusionist-V01_05_03");
        china.icons.push_back("noise-rabbit");
        china.icons.push_back("pixel-rabbit");
        
        dimensions[DRSDATA::CHINA] = china;
        
        dimension brazil("Brazil","Brazil", "Evidence Dimension Krypton", "EDK");
        brazil.songs.push_back(song("Gobbledygook","gobbledygook", 110, 4, 8, 6.0));
        brazil.songs[0].parts.push_back(part("gobbledygook-app beat", "Beat"));
        brazil.songs[0].parts.push_back(part("gobbledygook-app vocal", "Vocal"));
        brazil.songs[0].parts.push_back(part("gobbledygook-app 3-Audio", "Track 3"));
        brazil.songs[0].parts.push_back(part("gobbledygook-app 4-Audio", "T4"));
        brazil.songs[0].parts.push_back(part("gobbledygook-app 5-Audio", "T5"));
        brazil.songs[0].parts.push_back(part("gobbledygook-app 6-Audio", "T6"));
        brazil.songs[0].parts.push_back(part("gobbledygook-app 7-Audio", "T7"));
        brazil.songs[0].parts.push_back(part("gobbledygook-app 9-Audio", "T9"));
        
        brazil.icons.push_back("boulder");
        brazil.icons.push_back("EVD-Dragonarama_03");
        brazil.icons.push_back("EVD-Dragonarama_06");
        brazil.icons.push_back("EVD-Dragonarama_09");
        brazil.icons.push_back("EVD-Gobbling-Goblin_02");
        brazil.icons.push_back("EVD-Gobbling-Goblin_05");
        brazil.icons.push_back("EVD-Gobbling-Goblin_08");
        brazil.icons.push_back("Gift-box");
        brazil.icons.push_back("Split-D-Black-Stripe_10");
        
        dimensions[DRSDATA::BRAZIL] = brazil;
        
        dimension croatia("Croatia", "Croatia", "The Split Dimension", "splitdimension");
        croatia.songs.push_back(song("Journey To The End", "Journey To The End", 160, 4, 16, 2.0));
        croatia.songs[0].parts.push_back(part("journey to the end - final - app big melod", "Melody"));
        croatia.songs[0].parts.push_back(part("journey to the end - final - app intense", "Intense"));
        croatia.songs[0].parts.push_back(part("journey to the end - final - app mid break", "Mid Break"));
        croatia.songs[0].parts.push_back(part("journey to the end - final - app strings", "Strings"));
        croatia.songs[0].parts.push_back(part("journey to the end - final - app 2-Audio", "T2"));
        croatia.songs[0].parts.push_back(part("journey to the end - final - app 3-Audio", "T3"));
        croatia.songs[0].parts.push_back(part("journey to the end - final - app 4-Audio", "T4"));
        croatia.songs[0].parts.push_back(part("journey to the end - final - app 8-Audio", "T8"));
        
        croatia.icons.push_back("old-dimension-map-2");
        croatia.icons.push_back("old-dimension-map");
        croatia.icons.push_back("Split-D-Black-Stripe_03");
        croatia.icons.push_back("Split-D-Black-Stripe_07");
        croatia.icons.push_back("Split-D-Black-Stripe_10");
        croatia.icons.push_back("Split-D-Smoke-Samurai_02");
        croatia.icons.push_back("Split-D-Smoke-Samurai_05");
        croatia.icons.push_back("Split-D-Smoke-Samurai_07");
        
        dimensions[DRSDATA::CROATIA] = croatia;
        
        dimension germany("Germany", "Germany", "D-Tron", "Dtron background");
        germany.songs.push_back(song("Everyday Is A Red Day", "RedDay", 120, 4, 16, 3.0));
        germany.songs[0].parts.push_back(part("everyday is red day - app 1-Audio","T1"));
        germany.songs[0].parts.push_back(part("everyday is red day - app 2-Audio","T2"));
        germany.songs[0].parts.push_back(part("everyday is red day - app 3-Audio","T3"));
        germany.songs[0].parts.push_back(part("everyday is red day - app Beat","Beat"));
        germany.songs[0].parts.push_back(part("everyday is red day - app Clav","Clav"));
        germany.songs[0].parts.push_back(part("everyday is red day - app Pluck","Pluck"));
        germany.songs[0].parts.push_back(part("everyday is red day - app Red vox","Vox"));
        
        germany.icons.push_back("D-Tron-Aaron-Springs_03");
        germany.icons.push_back("D-Tron-Aaron-Springs_07");
        germany.icons.push_back("D-Tron-Aaron-Springs_09");
        germany.icons.push_back("D-Tron-D-Dash_03");
        germany.icons.push_back("D-Tron-D-Dash_06");
        germany.icons.push_back("D-Tron-D-Dash_09");
        germany.icons.push_back("D-TRon-Red_03");
        germany.icons.push_back("D-TRon-Red_07");
        germany.icons.push_back("D-TRon-Red_09");
        germany.icons.push_back("Lasagne");
        germany.icons.push_back("pizza");
        
        dimensions[DRSDATA::GERMANY] = germany;
        
        dimension japan("Japan", "Japan", "The Land Of The Golden Duke", "LOTGD Backdrop");
        japan.songs.push_back(song("Edna and Neyrod", "EdnaAndNeyrod", 120, 4, 16, 2.0));
        japan.songs[0].parts.push_back(part("edna and neyrod - app 5-Audio", "T5"));
        japan.songs[0].parts.push_back(part("edna and neyrod - app 7-Audio", "T7"));
        japan.songs[0].parts.push_back(part("edna and neyrod - app 11-Audio", "T11"));
        japan.songs[0].parts.push_back(part("edna and neyrod - app 12-Audio", "T12"));
        japan.songs[0].parts.push_back(part("edna and neyrod - app drums", "Drums"));
        japan.songs[0].parts.push_back(part("edna and neyrod - app piano", "Piano"));
        japan.songs[0].parts.push_back(part("edna and neyrod - app strings", "Strings"));
        japan.songs[0].parts.push_back(part("edna and neyrod - app wobbles", "Wobbles"));
        
        japan.icons.push_back("LOTGD-King-Neyrod_03");
        japan.icons.push_back("LOTGD-King-Neyrod_05");
        japan.icons.push_back("LOTGD-King-Neyrod_08");
        japan.icons.push_back("LOTGD-Princess-Carla-II_02");
        japan.icons.push_back("LOTGD-Princess-Carla-II_04");
        japan.icons.push_back("LOTGD-Princess-Carla-II_06");
        japan.icons.push_back("LOTGD-Queen-Edna_03");
        japan.icons.push_back("LOTGD-Queen-Edna_07");
        japan.icons.push_back("LOTGD-Queen-Edna_10");
        japan.icons.push_back("old-mac");
        
        dimensions[DRSDATA::JAPAN] = japan;
        
        dimension southAf("SouthAfrica", "South Africa", "The Cook House Dimension", "cookhouse background2");
        southAf.songs.push_back(song("Mama's Makin' Bread", "MamasMakinBread", 110, 4, 8, 2.0));
        southAf.songs[0].parts.push_back(part("mamas bakin bread - app 2-Audio","T2"));
        southAf.songs[0].parts.push_back(part("mamas bakin bread - app 4-Audio","T4"));
        southAf.songs[0].parts.push_back(part("mamas bakin bread - app Arcade","Arcade"));
        southAf.songs[0].parts.push_back(part("mamas bakin bread - app Car horn","Car Horn"));
        southAf.songs[0].parts.push_back(part("mamas bakin bread - app Horn sect","Horn Section"));
        southAf.songs[0].parts.push_back(part("mamas bakin bread - app marim","Marim"));
        southAf.songs[0].parts.push_back(part("mamas bakin bread - app sis_mary vox","Vox"));
        southAf.songs[0].parts.push_back(part("mamas bakin bread - app VOX Effcts","Vox Effects"));
        
        southAf.icons.push_back("Cook-House-Mama-Cous-Cous_03");
        southAf.icons.push_back("Cook-House-Mama-Cous-Cous_05");
        southAf.icons.push_back("Cook-House-Mama-Cous-Cous_07");
        southAf.icons.push_back("Cook-House-Sleepy-Eye-Paps_03");
        southAf.icons.push_back("Cook-House-Sleepy-Eye-Paps_06");
        southAf.icons.push_back("Cook-House-Sleepy-Eye-Paps_09");
        southAf.icons.push_back("cooker");
        southAf.icons.push_back("Fried-Chicken-Leg");
        southAf.icons.push_back("LOTGD-King-Neyrod_08");
        southAf.icons.push_back("Omelette");
        southAf.icons.push_back("sleepingcloud");
        
        dimensions[DRSDATA::SOUTH_AFRICA] = southAf;
        
        dimension uk("UK","UK","Dimension Domino", "UK backdrop2");
        uk.songs.push_back(song("Forever", "Forever", 96, 4, 8.25, 2.0));
        uk.songs[0].parts.push_back(part("Forever - app Beats", "Beats"));
        uk.songs[0].parts.push_back(part("Forever - app Claps", "Claps"));
        uk.songs[0].parts.push_back(part("Forever - app E piano Bass", "Piano Bass"));
        uk.songs[0].parts.push_back(part("Forever - app E Piano", "Electric Piano"));
        uk.songs[0].parts.push_back(part("Forever - app Idensity", "Idensity"));
        uk.songs[0].parts.push_back(part("Forever - app Lead Vox", "Lead Vox"));
        
        uk.icons.push_back("Domino-D-Tranquility_03");
        uk.icons.push_back("Domino-D-Tranquility_07");
        uk.icons.push_back("Domino-D-Tranquility_10");
        uk.icons.push_back("Domino-D-Zyax_02");
        uk.icons.push_back("Domino-D-Zyax_04");
        uk.icons.push_back("Domino-D-Zyax_07");
        uk.icons.push_back("speeder-300x");
        uk.icons.push_back("tower");
        
        dimensions[DRSDATA::UK] = uk;

    }
};




#endif
