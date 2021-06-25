using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tile
{
    public Vector3 position;
    public List<Resource> resourceList = new List<Resource>();

    public Tile(Vector3 position)
    {
        this.position = position;
    }

    public int getResourceCountByType(ResourceType type)
    {
        int count = 0;
        for (int i = 0; i < resourceList.Count; i++)
        {
            if (resourceList[i].type == type)
            {
                count += 1;
            }
        }
        return count;
    }

    public void addResourceByType(ResourceType type)
    {
        Vector3 pos = new Vector3(position.x + Random.Range(-0.4f, 0.4f), 0.05f, position.z + Random.Range(-0.4f, 0.4f));
        int count = getResourceCountByType(type);
        if (count < 20) {
            GameObject gameObject = Utils.createObject(pos, Utils.resourceAssets[(int)type]);
            resourceList.Add(new Resource(type, gameObject));
        }
        else
        {
            resourceList.Add(new Resource(type, null));
        }
    }

    public void removeResourceByType(ResourceType type)
    {
        for (int i = 0; i < resourceList.Count; i++)
        {
            if (resourceList[i].type == type)
            {
                if (resourceList[i].gameObject != null)
                {
                    Object.Destroy(resourceList[i].gameObject);
                }
                resourceList.RemoveAt(i);
                break;
            }
        }
    }
}
