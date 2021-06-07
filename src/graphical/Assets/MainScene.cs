using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class MainScene : MonoBehaviour
{
    public TCPTestClient socketClient = new TCPTestClient();

    static GameObject createPlane(Vector3 position, Vector3 scale, Color color) {
        GameObject plane = GameObject.CreatePrimitive(PrimitiveType.Plane);
        plane.transform.position = position;
        plane.transform.localScale = scale;
        if (color != Color.black && false)
        {
            plane.GetComponent<Renderer>().material.color = Random.ColorHSV(0f, 1f, 1f, 1f, 0.5f, 1f);
        } else {
            plane.GetComponent<Renderer>().material.color = color;
        }
        return plane;
    }

    static GameObject createTrontorianObject(Vector3 position) {
        GameObject instance = Instantiate(Resources.Load("Models/Trontorian/Minotaur@Walk", typeof(GameObject))) as GameObject;
        instance.transform.position = position;
        instance.transform.localScale = new Vector3(10, 10, 10);
        UnityEditor.AssetDatabase.LoadAssetAtPath("Assets/Resources/Models/Trontorian/Minotaur@Walk", typeof(Motion[]));
        var clips = Resources.FindObjectsOfTypeAll<AnimationClip>();
        if (instance.GetComponent<Animation>() == null)
        {
            instance.AddComponent<Animation>();
        }
        Animation anim = instance.GetComponent<Animation>();
        anim.clip = clips[0];
        anim.wrapMode = WrapMode.Loop;
        anim.Play();
        return instance;
    }

    public class Trontorian
    {
        public int uid { get; private set; }
        public string team { get; private set; }
        public int level { get; private set; }
        public int orientation { get; private set; }
        public Vector3 position { get; private set; }
        public GameObject gameObject { get; private set; }

        public Trontorian(int uid, float x, float y, int orientation, int level, string team)
        {
            this.uid = uid;
            this.position = new Vector3(x, 0, y);
            this.orientation = orientation;
            this.level = level;
            this.team = team;
            this.gameObject = createTrontorianObject(this.position);
        }
    }

    static void generateMap(float w, float h)
    {
        for (float y = 0.5f; y < w; y++)
        {
            for (float x = 0.5f; x < h; x++)
            {
                createPlane(new Vector3(x, 0, y), new Vector3(0.09f, 1, 0.09f), Color.red);
               
                createPlane(new Vector3(x + 0.475f, 0, y), new Vector3(0.005f, 1, 0.09f), Color.black);
                createPlane(new Vector3(x - 0.475f, 0, y), new Vector3(0.005f, 1, 0.09f), Color.black);

                createPlane(new Vector3(x, 0, y + 0.475f), new Vector3(0.1f, 1, 0.005f), Color.black);
                createPlane(new Vector3(x, 0, y - 0.475f), new Vector3(0.1f, 1, 0.005f), Color.black);
            }
        }
    }

    private float waitTime = 0.05f;
    private float timer = 0.0f;
    private float x = 0.0f;
    private Trontorian trontorian;
    // Start is called before the first frame update
    void Start()
    {
        // socketClient.ConnectToTcpServer();
        generateMap(24f, 24f);
        trontorian = new Trontorian(1, 9.5f, 10.5f, 1, 1, "Team 1");
        Trontorian trontorian2 = new Trontorian(1, 19.5f, 10.5f, 1, 1, "Team 1");
        Trontorian trontorian3 = new Trontorian(1, 9.5f, 15.5f, 1, 1, "Team 1");
    }

    // Update is called once per frame
    void Update()
    {
        timer += Time.deltaTime;
        if (timer < waitTime)
        {
            return;
        }
        timer = timer - waitTime;
        x += 0.05f;
        trontorian.gameObject.transform.position = new Vector3(transform.position.x, 0, x);

    }
}
