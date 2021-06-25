using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainScene : MonoBehaviour
{
    public RectTransform _loadingIcon;

    public TCPTestClient socketClient;

    void generateMap(float w, float h)
    {
        GameObject cube = GameObject.CreatePrimitive(PrimitiveType.Cube);
        cube.transform.position = new Vector3(w / 2, -0.13f, h / 2);
        cube.transform.localScale = new Vector3(w, 0.25f, h);
        Material newMat = Resources.Load("Materials/dirt", typeof(Material)) as Material;
        cube.GetComponent<Renderer>().material = newMat;

        for (float y = 0.5f; y < w; y++)
        {
            for (float x = 0.5f; x < h; x++)
            {
                Vector3 pos = new Vector3(x, 0, y);
                Utils.createPlane(pos, new Vector3(0.09f, 1, 0.09f));

                Utils.tileList.Add(new Tile(pos));
            }
        }

        GameObject plane = GameObject.CreatePrimitive(PrimitiveType.Plane);
        plane.transform.position = new Vector3(w / 2, -0.01f, h / 2);
        plane.transform.localScale = new Vector3(10, 10, 10);
        Material planeMat = Resources.Load("Nokobot/GreekTemple/03_Materials/Ares Statue/Ares_Body", typeof(Material)) as Material;
        plane.GetComponent<Renderer>().material = planeMat;

        GameObject temple = Utils.createPrefabObject(new Vector3(w / 2, 0, h + 1 + w / 25), "Nokobot/GreekTemple/01_Prefabs/Structure_Presets/Colonnade_Short_WithPediment");
        temple.transform.localScale = new Vector3(w / 25, 0.5f, w / 25);

        GameObject statusAres = Utils.createPrefabObject(new Vector3(-w / 4, 0, 10), "Nokobot/GreekTemple/01_Prefabs/Statues/Statue_Ares");
        statusAres.transform.localScale = new Vector3(0.5f, 0.5f, 0.5f);
        statusAres.transform.Rotate(new Vector3(0, 110, 0));

        GameObject statusHydra = Utils.createPrefabObject(new Vector3(w + 3, 0, 7), "Nokobot/GreekTemple/01_Prefabs/Statues/Statue_Hydra");
        statusHydra.transform.localScale = new Vector3(0.5f, 0.5f, 0.5f);
        statusHydra.transform.Rotate(new Vector3(0, -80, 0));   

        GameObject pot1 = Utils.createPrefabObject(new Vector3(w + 3, 0, 11), "Nokobot/GreekTemple/01_Prefabs/Vases/Vase_03");
        pot1.transform.Rotate(new Vector3(-7, -23, -67));   
        GameObject pot2 = Utils.createPrefabObject(new Vector3(w + 3, 0, 3), "Nokobot/GreekTemple/01_Prefabs/Vases/Vase_02");
        pot2.transform.Rotate(new Vector3(0, 10, 0));   
        GameObject pot3 = Utils.createPrefabObject(new Vector3(-w / 4, 0, 4), "Nokobot/GreekTemple/01_Prefabs/Vases/Vase_01");
        pot3.transform.Rotate(new Vector3(0, 4, 0));
    }

    private float waitTime = 0.05f;
    private float waitKillTime = 6f;
    private float killTimer = 0.0f;
    private float timer = 0.0f;
    private float updateWaitTime = 1f;
    private float updateServerTimer = 0.0f;

    public List<string> serverMessages;
    public void stockMessage(string message)
    {
        serverMessages.Add(message);
    }

    void Start()
    {
        Utils.resourceAssets[0] = "Models/Food/Apple";
        Utils.resourceAssets[1] = "Models/Stone/Linemate";
        Utils.resourceAssets[2] = "Models/Stone/Deraumere";
        Utils.resourceAssets[3] = "Models/Stone/Sibur";
        Utils.resourceAssets[4] = "Models/Stone/Mendiane";
        Utils.resourceAssets[5] = "Models/Stone/Phiras";
        Utils.resourceAssets[6] = "Models/Stone/Thystame";

        Utils.defaultTeamColors[0] = Color.red;
        Utils.defaultTeamColors[1] = Color.blue;
        Utils.defaultTeamColors[2] = Color.green;
        Utils.defaultTeamColors[3] = Color.yellow;
        Utils.defaultTeamColors[4] = Color.gray;

        socketClient = new TCPTestClient(this);
        socketClient.ConnectToTcpServer();
    }

    void moveTrontorians()
    {
        timer += Time.deltaTime;
        if (timer < waitTime)
        {
            return;
        }
        timer = timer - waitTime;
        for (int i = 0; i < Utils.trontorianList.Count; i++)
        {
            GameObject trontorian = Utils.trontorianList[i].gameObject;
            if (trontorian.transform.position != Utils.trontorianList[i].positionToGo)
            {
                Utils.trontorianList[i].sphere.transform.position = new Vector3(trontorian.transform.position.x, 1.25f, trontorian.transform.position.z);
                Utils.trontorianList[i].updatePosition();
            }
            else
            {
                Utils.trontorianList[i].waitForNextAction = false;
                Utils.trontorianList[i].idle();
            }
        }
    }

    void killTrontorians()
    {
        killTimer += Time.deltaTime;
        if (killTimer < waitKillTime)
        {
            return;
        }
        killTimer = killTimer - waitKillTime;
        for (int i = 0; i < Utils.trontorianList.Count; i++)
        {
            if (Utils.trontorianList[i].isDead)
            {
                Object.Destroy(Utils.trontorianList[i].gameObject);
                Utils.trontorianList.RemoveAt(i);
            }
        }
    }

    void checkServerMessages()
    {
        bool shouldSkip = false;

        for (int idxMessage = 0; idxMessage < serverMessages.Count; idxMessage++)
		{
            string[] parts = serverMessages[idxMessage].Split(' ');
            switch (parts[0])
            {
                case "error":
                    SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex - 1);
                    break;
                case "msz":
                    _loadingIcon.GetComponent<CanvasGroup>().alpha = 0;
                    Utils.map_x = float.Parse(parts[1]);
                    Utils.map_y = float.Parse(parts[2]);
                    generateMap(Utils.map_x, Utils.map_y);
                    break;
                case "tna":
                    string teamName = parts[1];
                    Utils.teamColors[teamName] = Utils.defaultTeamColors[Utils.teamColorIdx];  
                    Utils.teamColorIdx++;
                    break;
                case "pnw":
                    Utils.trontorianList.Add(new Trontorian(int.Parse(parts[1]), float.Parse(parts[2]), float.Parse(parts[3]), int.Parse(parts[4]), int.Parse(parts[5]), parts[6]));
                    break;
                case "bct":
                    try {
                        Tile tile = Utils.getTileByPos(new Vector3(float.Parse(parts[1]) + 0.5f, 0, float.Parse(parts[2]) + 0.5f));

                        for (int resourceIdx = 3; resourceIdx < 10; resourceIdx++)
                        {
                            ResourceType resourceType = (ResourceType)(resourceIdx - 3);
                            int serverCount = int.Parse(parts[resourceIdx]);
                            int count = serverCount - tile.getResourceCountByType(resourceType);
                            if (count < 0)
                            {
                                for (int i = count; i < 0; i++)
                                {
                                    tile.removeResourceByType(resourceType);
                                }
                            } else {
                                for (int i = 0; i < count; i++)
                                {
                                    tile.addResourceByType(resourceType);
                                }
                            }
                        }
                    } catch {
                        //
                    }
                    break;
                case "pdi":
                {
                    int uid = int.Parse(parts[1]);
                    for (int idx = 0; idx < Utils.trontorianList.Count; idx++)
                    {
                        if (Utils.trontorianList[idx].uid == uid)
                        {
                            Utils.trontorianList[idx].Kill();
                            break;
                        }
                    }
                    break;
                }
                case "ppo":
                {
                    int uid = int.Parse(parts[1]);
                    Trontorian trontorian = Utils.getTrontorianByUid(uid);
                    if (trontorian.waitForNextAction)
                    {
                        shouldSkip = true;
                        break;
                    }
                    Vector3 newPos = new Vector3(float.Parse(parts[2]) + 0.5f, 0, float.Parse(parts[3]) + 0.5f);
                    trontorian.setOrientation(int.Parse(parts[4]));
                    if (newPos != trontorian.gameObject.transform.position)
                    {
                        if (Vector3.Distance(newPos, trontorian.positionToGo) > 2) {
                            trontorian.gameObject.transform.position = newPos;
                            trontorian.positionToGo = trontorian.gameObject.transform.position;
                        } else {
                            trontorian.waitForNextAction = true;
                            trontorian.move();
                        }
                    }
                    break;
                }
                case "pdr":
                case "pgt":
                {
                    socketClient.SendMessage("pin " + parts[1] + "\n");
                    break;
                }
                case "pin":
                {
                    int uid = int.Parse(parts[1]);
                    for (int resourceIdx = 3; resourceIdx < 10; resourceIdx++)
                    {
                        ResourceType resourceType = (ResourceType)(resourceIdx - 3);
                        int count = int.Parse(parts[resourceIdx]);
                        
                    }
                    break;
                }
                case "pic":
                {
                    Vector3 pos = new Vector3(float.Parse(parts[1]) + 0.5f, 0, float.Parse(parts[2]) + 0.5f);
                    Tile tile = Utils.getTileByPos(pos);
                    Trontorian masterTrontorian = Utils.getTrontorianByUid(int.Parse(parts[4]));
                    masterTrontorian.jump();
                    for (int i = 5; i < parts.Length; i++)
                    {
                        int uid = int.Parse(parts[i]);
                        Trontorian otherTrontorian = Utils.getTrontorianByUid(int.Parse(parts[4]));
                        otherTrontorian.jump();
                    }
                    break;
                }
                case "pie":
                {
                    Vector3 pos = new Vector3(float.Parse(parts[1]) + 0.5f, 0, float.Parse(parts[2]) + 0.5f);
                    for (int idx = 0; idx < Utils.trontorianList.Count; idx++)
                    {
                        if (Utils.trontorianList[idx].position == pos)
                        {
                            Utils.trontorianList[idx].stopJump();
                        }
                    }
                    break;
                }
                case "enw":
                {
                    Utils.eggList.Add(new Egg(int.Parse(parts[1]), int.Parse(parts[2]), new Vector3(float.Parse(parts[3]) + 0.5f, 0.1f, int.Parse(parts[4]) + 0.5f)));
                    break;
                }
                case "edi":
                case "eht":
                {
                    int uid = int.Parse(parts[1]);
                    for (int i = 0; i < Utils.eggList.Count; i++)
                    {
                        if (Utils.eggList[i].uid == uid)
                        {
                            Utils.eggList[i].Destroy();
                            Utils.eggList.RemoveAt(i);
                            break;
                        }
                    }
                    break;
                }
                case "seg":
                {
                    Utils.winnerTeamName = parts[1];
                    SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
                    break;
                }
            }
            if (!shouldSkip)
            {
                serverMessages.RemoveAt(idxMessage);
            }
        }
    }

    void updateServerData()
    {
        updateServerTimer += Time.deltaTime;
        if (updateServerTimer < updateWaitTime)
        {
            return;
        }
        updateServerTimer = updateServerTimer - updateWaitTime;
        socketClient.SendMessage("mct\n");
    }

    // Update is called once per frame
    void Update()
    {
        checkServerMessages();
        updateServerData();
        killTrontorians();
        moveTrontorians();
    }

    private void OnDestroy() {
        socketClient.clientReceiveThread.Abort();
    }
}
