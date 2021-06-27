using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class Utils
{
    public static Dictionary<int, string> resourceAssets = new Dictionary<int, string>();

    public static List<Tile> tileList = new List<Tile>();
    public static List<Trontorian> trontorianList = new List<Trontorian>();
    public static List<Egg> eggList = new List<Egg>();

    public static int teamColorIdx = 0;
    public static Dictionary<int, Color> defaultTeamColors = new Dictionary<int, Color>();
    public static Dictionary<string, Color> teamColors = new Dictionary<string, Color>();
    public static List<string> teamNames = new List<string>();

    public static float map_x = 0;
    public static float map_y = 0;

    public static float sgt = 0;

    public static GameObject followTrontorian = null;

    public static string winnerTeamName;

    public static AnimationClip findAnimationByName(string name) {
        var clips = Resources.FindObjectsOfTypeAll<AnimationClip>();

        for (int i = 0; i < clips.Length; i++)
        {  
            if (clips[i].name == name)
            {
                return clips[i];
            }
        }
        return null;
    }

    public static GameObject createSphere(Vector3 position, Vector3 scale, Color color) {
        GameObject sphere = GameObject.CreatePrimitive(PrimitiveType.Sphere);
        sphere.transform.position = position;
        sphere.transform.localScale = scale;
        sphere.GetComponent<Renderer>().material.color = color;
        return sphere;
    }

    public static GameObject createPlane(Vector3 position, Vector3 scale) {
        GameObject plane = GameObject.CreatePrimitive(PrimitiveType.Plane);
        plane.transform.position = position;
        plane.transform.localScale = scale;
        Material newMat = Resources.Load("Nokobot/GreekTemple/03_Materials/Ares Statue/Pedestal_Ares_Heads", typeof(Material)) as Material;
        plane.GetComponent<Renderer>().material = newMat;
        return plane;
    }

    public static GameObject createColorPlane(Vector3 position, Vector3 scale, Color color) {
        GameObject plane = GameObject.CreatePrimitive(PrimitiveType.Plane);
        plane.transform.position = position;
        plane.transform.localScale = scale;
        plane.GetComponent<Renderer>().material.color = color;
        return plane;
    }

    public static GameObject createTrontorianObject(Vector3 position) {
        GameObject instance = Object.Instantiate(Resources.Load("Models/Trontorian/Minotaur", typeof(GameObject))) as GameObject;
        instance.transform.position = position;
        instance.transform.localScale = new Vector3(10, 10, 10);
        var clips = Resources.FindObjectsOfTypeAll<AnimationClip>();
        if (instance.GetComponent<Animation>() == null)
        {
            instance.AddComponent<Animation>();
        }
        return instance;
    }

    public static GameObject createPrefabObject(Vector3 position, string path) {
        GameObject instance = Object.Instantiate(Resources.Load(path, typeof(GameObject))) as GameObject;
        instance.transform.position = position;

        return instance;
    }
    public static GameObject createObject(Vector3 position, string path) {
        GameObject instance = createPrefabObject(position, path);
        if (path == resourceAssets[0])
        {
            instance.transform.localScale = new Vector3(0.15f, 0.15f, 0.15f);
        }
        else
        {
            instance.transform.localScale = new Vector3(0.5f, 0.5f, 0.5f);
        }
        instance.transform.Rotate(new Vector3(0, Random.Range(0f, 180f), 0));
        return instance;
    }

    public static Tile getTileByPos(Vector3 position)
    {
        for (int i = 0; i < tileList.Count; i++)
        {
            if (tileList[i].position == position)
            {
                return tileList[i];
            }
        }
        return null;
    }

    public static Trontorian getTrontorianByUid(int uid)
    {
        for (int idx = 0; idx < trontorianList.Count; idx++)
        {
            if (trontorianList[idx].uid == uid)
            {
                return trontorianList[idx];
            }
        }
        return null;
    }

}
