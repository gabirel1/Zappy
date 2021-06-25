using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Egg
{
    public int uid;
    public int playerUid;
    public GameObject gameObject;
    public GameObject particle;

    public Egg(int eggNumber, int playerNumber, Vector3 position)
    {
        this.uid = eggNumber;
        this.playerUid = playerNumber;
        this.gameObject = Utils.createObject(position, "Models/Egg/Egg");
        this.gameObject.transform.eulerAngles = new Vector3(-90, this.gameObject.transform.eulerAngles.y, this.gameObject.transform.eulerAngles.z);
        this.gameObject.transform.localScale = new Vector3(1, 1, 1);
        this.particle = Utils.createObject(position, "Particles/eggEffect");
        this.particle.transform.localScale = new Vector3(0.1f, 0.1f, 0.1f);
    }

    public void Destroy()
    {
        Object.Destroy(this.particle);
        Object.Destroy(this.gameObject);
    }
}
