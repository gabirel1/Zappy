using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum ResourceType
{
    FOOD = 0,
    LINEMATE = 1,
    DERAUMERE = 2,
    SIBUR = 3,
    MENDIANE = 4,
    PHIRAS = 5,
    THYSTAME = 6
};

public class Resource
    {
        public ResourceType type;
        public GameObject gameObject;

        public Resource(ResourceType type, GameObject gameObject)
        {
            this.type = type;
            this.gameObject = gameObject;
        }
    }
