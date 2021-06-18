using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainScene : MonoBehaviour
{
    public RectTransform _loadingIcon;

    public TCPTestClient socketClient;

    private float map_x = 0;
    private float map_y = 0;

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
    }

    private float waitTime = 0.05f;
    private float timer = 0.0f;
    private float updateWaitTime = 1f;
    private float updateServerTimer = 0.0f;

    private List<Trontorian> trontorianList = new List<Trontorian>();
    private List<Egg> eggList = new List<Egg>();

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
        for (int i = 0; i < trontorianList.Count; i++)
        {
            if (trontorianList[i].gameObject.transform.position != trontorianList[i].positionToGo)
            {
                trontorianList[i].updatePosition();
            } else
            {
                trontorianList[i].waitForNextAction = false;
                trontorianList[i].idle();
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
                    map_x = float.Parse(parts[1]);
                    map_y = float.Parse(parts[2]);
                    generateMap(map_x, map_y);
                    break;
                case "pnw":
                    trontorianList.Add(new Trontorian(int.Parse(parts[1]), float.Parse(parts[2]) % map_x, float.Parse(parts[3]) % map_y, int.Parse(parts[4]), int.Parse(parts[5]), parts[6]));
                    break;
                case "bct":
                    try {
                        Tile tile = Utils.getTileByPos(new Vector3(float.Parse(parts[1]) + 0.5f, 0, float.Parse(parts[2]) + 0.5f));

                        for (int resourceIdx = 3; resourceIdx < 10; resourceIdx++)
                        {
                            ResourceType resourceType = (ResourceType)(resourceIdx - 3);
                            int count = int.Parse(parts[resourceIdx]) - tile.getResourceCountByType(resourceType);
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
                    for (int idx = 0; idx < trontorianList.Count; idx++)
                    {
                        if (trontorianList[idx].uid == uid)
                        {
                            Destroy(trontorianList[idx].gameObject);
                            trontorianList.RemoveAt(idx);
                            break;
                        }
                    }
                    break;
                }
                case "ppo":
                {
                    int uid = int.Parse(parts[1]);
                    for (int idx = 0; idx < trontorianList.Count; idx++)
                    {
                        if (trontorianList[idx].uid == uid)
                        {
                            if (trontorianList[idx].waitForNextAction)
                            {
                                shouldSkip = true;
                                break;
                            }
                            Vector3 newPos = new Vector3((float.Parse(parts[2]) % map_x) + 0.5f, 0, (float.Parse(parts[3]) % map_y) + 0.5f);
                            trontorianList[idx].setOrientation(int.Parse(parts[4]));
                            if (newPos != trontorianList[idx].gameObject.transform.position)
                            {
                                trontorianList[idx].waitForNextAction = true;
                                trontorianList[idx].move();
                            }
                            break;
                        }
                    }
                    break;
                }
                case "enw":
                {
                    eggList.Add(new Egg(int.Parse(parts[1]), int.Parse(parts[2]), new Vector3(float.Parse(parts[3]) + 0.5f, 0.1f, int.Parse(parts[4]) + 0.5f)));
                    break;
                }
                case "eht":
                {
                    
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
        moveTrontorians();
    }

    private void OnDestroy() {
        socketClient.clientReceiveThread.Abort();
    }
}
