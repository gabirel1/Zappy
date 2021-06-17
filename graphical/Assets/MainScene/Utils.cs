using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class Utils
{
    public static Dictionary<int, string> resourceAssets = new Dictionary<int, string>();

    public static List<Tile> tileList = new List<Tile>();

    public static AnimationClip findAnimationByName(string name) {
        var clips = Resources.FindObjectsOfTypeAll<AnimationClip>();
        AnimationClip clip = null;
        for (int i = 0; i < clips.Length; i++)
        {
            if (clips[i].name == name)
            {
                return clips[i];
            }
        }
        return null;
    }

    public static GameObject createPlane(Vector3 position, Vector3 scale) {
        GameObject plane = GameObject.CreatePrimitive(PrimitiveType.Plane);
        plane.transform.position = position;
        plane.transform.localScale = scale;
        Material newMat = Resources.Load("Materials/grass", typeof(Material)) as Material;
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
        GameObject instance = Object.Instantiate(Resources.Load("Models/Trontorian/Minotaur@Idle", typeof(GameObject))) as GameObject;
        instance.transform.position = position;
        instance.transform.localScale = new Vector3(10, 10, 10);
        var clips = Resources.FindObjectsOfTypeAll<AnimationClip>();
        AnimationClip clip = Utils.findAnimationByName("Idle");
        if (instance.GetComponent<Animation>() == null)
        {
            instance.AddComponent<Animation>();
        }
        Animation anim = instance.GetComponent<Animation>();
        anim.clip = clip;
        anim.wrapMode = WrapMode.Loop;
        anim.Play();
        return instance;
    }

    public static GameObject createObject(Vector3 position, string path) {
        GameObject instance = Object.Instantiate(Resources.Load(path, typeof(GameObject))) as GameObject;
        instance.transform.position = position;
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

}
