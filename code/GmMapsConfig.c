#pragma once

GmMapConfig s_KamadanJewelOfIstanOutpost = {
    .map_id = MapId_KamadanJewelOfIstanOutpost,
    .map_file_id = 0x345CC,
    .n_spawnpoints = 1,
    .spawnpoints = {
        { -9067.f, 13218.f, 0 },
    },
} ;

GmMapConfig* GetMapConfigForMapId(MapId map_id)
{
    switch (map_id) {
    case MapId_KamadanJewelOfIstanOutpost:
        return &s_KamadanJewelOfIstanOutpost;
    default:
        return NULL;
    }
}
