using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;

public enum TrontorianState
{
    IDLE = 0,
    WALK = 1,
    JUMP = 2
}

public class TrontorianPosition
{
    public Vector3 position;
    public int orientation;

    public TrontorianPosition(Vector3 position, int orientation)
    {
        this.position = position;
        this.orientation = orientation;
    }
}

public class Trontorian
{
    public int uid { get; private set; }
    public string team { get; private set; }
    public int level { get; private set; }
    public int orientation { get; set; }
    public Vector3 position { get; private set; }
    public Vector3 positionToGo { get; set; }
    public List<TrontorianPosition> nextPositionList { get; set; } = new List<TrontorianPosition>();
    public GameObject gameObject { get; private set; } = null;
    public GameObject sphere { get; private set; }
    public bool waitForNextAction { get; set; }
    public TrontorianState state = TrontorianState.IDLE;
    public bool isDead = false;

    public List<Resource> inventory = new List<Resource>();

    public Dictionary<string, AnimationClip> clips = new Dictionary<string, AnimationClip>();

    public Trontorian(int uid, float x, float y, int orientation, int level, string team)
    {
        this.uid = uid;
        this.position = new Vector3(x + 0.5f, 0, y + 0.5f);
        this.positionToGo = position;
        this.level = level;
        this.team = team;
        this.orientation = orientation;

        for (int i = 0; i < Utils.eggList.Count; i++)
        {
            if (Utils.eggList[i].uid == uid)
            {
                return;
            }
        }
        initGameObject();
    }

    public void initGameObject()
    {
        this.gameObject = Utils.createTrontorianObject(this.position);
        this.gameObject.AddComponent<BoxCollider>();
        this.gameObject.GetComponent<BoxCollider>().size = new Vector3(0.05f, 0.1f, 0.05f);

        this.gameObject.name = "Minotaur" + this.uid.ToString();
        setOrientation(orientation);
        initAnimations();
        playAnimation("Idle", true);

        this.sphere = Utils.createSphere(new Vector3(gameObject.transform.position.x, 5, gameObject.transform.position.y), new Vector3(0.1f, 0.1f, 0.1f), Utils.teamColors[team]);
    }

    public int getResourceCountByType(ResourceType type)
    {
        int count = 0;
        for (int i = 0; i < inventory.Count; i++)
        {
            if (inventory[i].type == type)
            {
                count += 1;
            }
        }
        return count;
    }

    public void addResourceByType(ResourceType type)
    {
        inventory.Add(new Resource(type, null));
    }

    public void removeResourceByType(ResourceType type)
    {
        for (int i = 0; i < inventory.Count; i++)
        {
            if (inventory[i].type == type)
            {
                inventory.RemoveAt(i);
                break;
            }
        }
    }

    private void initAnimations()
    {
        Animation anim = this.gameObject.GetComponent<Animation>();
        AnimationClip clip = Utils.findAnimationByName("Walk");
        anim.AddClip(clip, clip.name);
        clips["Walk"] = clip;
        clip = Utils.findAnimationByName("Idle");
        anim.AddClip(clip, clip.name);
        clips["Idle"] = clip;
        clip = Utils.findAnimationByName("Jump");
        anim.AddClip(clip, clip.name);
        clips["Jump"] = clip;
        clip = Utils.findAnimationByName("Death1");
        anim.AddClip(clip, clip.name);
        clips["Death1"] = clip;
    }

    private void playAnimation(string animationName, bool loop)
    {
        Animation anim = gameObject.GetComponent<Animation>();
        AnimationClip clip = clips[animationName];
        if (clip == null)
        {
            Debug.Log("Unable to play animation " + animationName);
            return;
        }
        anim.Stop();
        anim.clip = clip;
        if (loop)
        {
            anim.wrapMode = WrapMode.Loop;
        }
        else
        {
            anim.wrapMode = WrapMode.Once;
        }
        anim.Play();
    }

    public void move()
    {
        state = TrontorianState.WALK;
        playAnimation("Walk", true);
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
        if (state == TrontorianState.IDLE || state == TrontorianState.JUMP)
        {
            return;
        }
        state = TrontorianState.IDLE;
        playAnimation("Idle", true);
    }

    public void jump()
    {
        state = TrontorianState.JUMP;
        playAnimation("Jump", true);
    }

    public void stopJump()
    {
        state = TrontorianState.IDLE;
        playAnimation("Idle", true);
    }

    public void updatePosition()
    {
        var x = gameObject.transform.position.x;
        var z = gameObject.transform.position.z;

        float delta = Utils.sgt / 140;
        float distance = Vector3.Distance(gameObject.transform.position, positionToGo);
        if (delta > distance)
        {
            delta = distance;
        }

        if (gameObject.transform.position.x < positionToGo.x)
        {
            x += delta;
        } else if (gameObject.transform.position.x > positionToGo.x)
        {
            x -= delta;
        } else if (gameObject.transform.position.z < positionToGo.z)
        {
            z += delta;
        } else if (gameObject.transform.position.z > positionToGo.z)
        {
            z -= delta;
        }
        gameObject.transform.position = new Vector3(x, 0, z);
    }

    public void setOrientation(int orientation)
    {
        this.orientation = orientation;
        this.gameObject.transform.eulerAngles = new Vector3(0, (orientation - 1) * 90, 0);
    }

    public void Kill()
    {
        playAnimation("Death1", false);
        Object.Destroy(this.sphere);
        this.isDead = true;
    }
}