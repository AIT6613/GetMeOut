#include "SoundManager.h"



SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
	//delete memory held for all sounds in list
	for(SoundListing listing : sounds)
	{
		Mix_FreeChunk(listing.sound);
	}
}

void SoundManager::loadSound(string name, string filePath)
{
	SoundListing listing;
	listing.name = name;
	listing.sound = Mix_LoadWAV(filePath.c_str());

	if (listing.sound != NULL)
	{
		sounds.push_back(listing);
	}
}

void SoundManager::playSound(string name)
{
	//look through list, if match name, play soung
	for(SoundListing listing : sounds)
	{
		if (listing.name == name)
		{
			//play sound we matched by name
			//params: channel to play on (can replace sound playing on specific channel or -1 to pick a free channel)
			//		sound to play
			//		loop (0 means play once, 1 means play once then play 1 loop of it, -1 infinite)
			Mix_PlayChannel(-1, listing.sound, 0);
			break;
		}
	}
}

SoundManager SoundManager::soundManager;
