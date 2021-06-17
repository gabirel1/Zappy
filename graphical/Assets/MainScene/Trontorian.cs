using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Trontorian
{
    public int uid { get; private set; }
    public string team { get; private set; }
    public int level { get; private set; }
    public int orientation { get; set; }
    public Vector3 position { get; private set; }
    public Vector3 positionToGo { get; set; }
    public GameObject gameObject { get; private set; }
    public bool waitForNextAction { get; set; }
    public bool isIdling = true;

    public Trontorian(int uid, float x, float y, int orientation, int level, string team)
    {
        this.uid = uid;
        this.position = new Vector3(x + 0.5f, 0, y + 0.5f);
        this.positionToGo = position;
        this.level = level;
        this.team = team;
        this.gameObject = Utils.createTrontorianObject(this.position);
        setOrientation(orientation);
    }

    public void move()
    {
        isIdling = false;
        Animation anim = gameObject.GetComponent<Animation>();
        AnimationClip clip = Utils.findAnimationByName("Walk");
        anim.Stop();
        anim.AddClip(clip, clip.name);
        anim.clip = clip;
        anim.wrapMode = WrapMode.Loop;
        anim.Play();
        switch (orientation)
        {
            case 1: // N
                positionToGo = new Vector3(gameObject.transform.position.x, 0, gameObject.transform.position.z + 1f);
                break;
            case 2: // E
                positionToGo = new Vector3(gameObject.transform.position.x + 1f, 0, gameObject.transform.position.z);
                break;
            case 3: // S
                positionToGo = new Vector3(gameObject.transform.position.x, 0, gameObject.transform.position.z - 1f);
                break;
            case 4: // W
                positionToGo = new Vector3(gameObject.transform.position.x - 1f, 0, gameObject.transform.position.z);
                break;

        }
    }

    public void idle()
    {
        if (isIdling)
        {
            return;
        }
        isIdling = true;
        AnimationClip clip = Utils.findAnimationByName("Idle");
        Animation anim = gameObject.GetComponent<Animation>();
        anim.Stop();
        anim.clip = clip;
        anim.wrapMode = WrapMode.Loop;
        anim.Play();
    }
    
    public void updatePosition()
    {
        var x = gameObject.transform.position.x;
        var z = gameObject.transform.position.z;

        if (gameObject.transform.position.x < positionToGo.x)
        {
            x += 0.1f;
        } else if (gameObject.transform.position.x > positionToGo.x)
        {
            x -= 0.1f;
        } else if (gameObject.transform.position.z < positionToGo.z)
        {
            z += 0.1f;
        } else if (gameObject.transform.position.z > positionToGo.z)
        {
            z -= 0.1f;
        }
        gameObject.transform.position = new Vector3(x, 0, z);
    }

    public void setOrientation(int orientation)
    {
        this.orientation = orientation;
        gameObject.transform.eulerAngles = new Vector3(0, (orientation - 1) * 90, 0);
    }
}