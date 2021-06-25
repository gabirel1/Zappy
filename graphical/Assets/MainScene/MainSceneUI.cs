using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;

public class MainSceneUI : MonoBehaviour
{
    public RectTransform _tileInfos;
    public TextMeshProUGUI _tileInfosCasePos;

    public TextMeshProUGUI _tileInfosFoodCount;
    public TextMeshProUGUI _tileInfosLinemateCount;
    public TextMeshProUGUI _tileInfosDeraumereCount;
    public TextMeshProUGUI _tileInfosSiburCount;
    public TextMeshProUGUI _tileInfosMendianeCount;
    public TextMeshProUGUI _tileInfosPhirasCount;
    public TextMeshProUGUI _tileInfosThystameCount;

    private GameObject savedWhitePlane;

    private Tile selectedTile = null;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    void updateCountFromTile(Tile tile)
    {
        _tileInfosFoodCount.text = tile.getResourceCountByType(ResourceType.FOOD).ToString();
        _tileInfosLinemateCount.text = tile.getResourceCountByType(ResourceType.LINEMATE).ToString();
        _tileInfosDeraumereCount.text = tile.getResourceCountByType(ResourceType.DERAUMERE).ToString();
        _tileInfosSiburCount.text = tile.getResourceCountByType(ResourceType.SIBUR).ToString();
        _tileInfosMendianeCount.text = tile.getResourceCountByType(ResourceType.MENDIANE).ToString();
        _tileInfosPhirasCount.text = tile.getResourceCountByType(ResourceType.PHIRAS).ToString();
        _tileInfosThystameCount.text = tile.getResourceCountByType(ResourceType.THYSTAME).ToString();
    }

    void handleClick()
    {
        if (selectedTile != null)
        {
            updateCountFromTile(selectedTile);
        }
        if (Input.GetKey(KeyCode.Escape))
        {
            _tileInfos.GetComponent<CanvasGroup>().alpha = 0;
            selectedTile = null;
        }
        if (Input.GetMouseButtonDown(0))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            
            if (Physics.Raycast(ray, out hit, 100))
            {
                GameObject gameObject = hit.transform.gameObject;
                Debug.Log(gameObject.name);
                if (gameObject.name == "Minotaure")
                {
                    Utils.followTrontorian = gameObject;
                    return;
                }
                if (gameObject.name != "Plane")
                {
                    return;
                }

                if (savedWhitePlane)
                {
                    Object.Destroy(savedWhitePlane);
                }

                Vector3 pos = gameObject.transform.position;
                pos.y += 0.001f;
                savedWhitePlane = Utils.createColorPlane(pos, new Vector3(0.09f, 1, 0.09f), Color.red);

                Tile tile = Utils.getTileByPos(gameObject.transform.position);

                if (tile == null)
                {
                    return;
                }
                selectedTile = tile;
                _tileInfos.GetComponent<CanvasGroup>().alpha = 1;
                _tileInfosCasePos.text = "Case " + (gameObject.transform.position.x - 0.5f) + ", " + (gameObject.transform.position.z - 0.5);

                updateCountFromTile(tile);
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        handleClick();
    }

    public void goBack()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex - 2);
    }
}
