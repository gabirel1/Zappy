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

    public TMP_Dropdown _teamDropdown;

    private GameObject savedWhitePlane;

    private Tile selectedTile = null;
    private string selectedTeam = null;

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

    void updateCountFromTeam(string teamName)
    {
        int foodCount = 0;
        int linemateCount = 0;
        int deraumereCount = 0;
        int siburCount = 0;
        int mendianeCount = 0;
        int phirasCount = 0;
        int thystameCount = 0;

        for (int i = 0; i < Utils.trontorianList.Count; i++)
        {
            Trontorian trontorian = Utils.trontorianList[i];
            if (trontorian.team == teamName)
            {
                foodCount = trontorian.getResourceCountByType(ResourceType.FOOD);
                linemateCount = trontorian.getResourceCountByType(ResourceType.LINEMATE);
                deraumereCount = trontorian.getResourceCountByType(ResourceType.DERAUMERE);
                siburCount = trontorian.getResourceCountByType(ResourceType.SIBUR);
                mendianeCount = trontorian.getResourceCountByType(ResourceType.MENDIANE);
                phirasCount = trontorian.getResourceCountByType(ResourceType.PHIRAS);
                thystameCount = trontorian.getResourceCountByType(ResourceType.THYSTAME);
            }
        }
        _tileInfosFoodCount.text = foodCount.ToString();
        _tileInfosLinemateCount.text = linemateCount.ToString();
        _tileInfosDeraumereCount.text = deraumereCount.ToString();
        _tileInfosSiburCount.text = siburCount.ToString();
        _tileInfosMendianeCount.text = mendianeCount.ToString();
        _tileInfosPhirasCount.text = phirasCount.ToString();
        _tileInfosThystameCount.text = thystameCount.ToString();
    }

    void updateCountFromPlayer(Trontorian trontorian)
    {
        _tileInfosFoodCount.text = trontorian.getResourceCountByType(ResourceType.FOOD).ToString();
        _tileInfosLinemateCount.text = trontorian.getResourceCountByType(ResourceType.LINEMATE).ToString();
        _tileInfosDeraumereCount.text = trontorian.getResourceCountByType(ResourceType.DERAUMERE).ToString();
        _tileInfosSiburCount.text = trontorian.getResourceCountByType(ResourceType.SIBUR).ToString();
        _tileInfosMendianeCount.text = trontorian.getResourceCountByType(ResourceType.MENDIANE).ToString();
        _tileInfosPhirasCount.text = trontorian.getResourceCountByType(ResourceType.PHIRAS).ToString();
        _tileInfosThystameCount.text = trontorian.getResourceCountByType(ResourceType.THYSTAME).ToString();
    }

    void handleClick()
    {
        if (Utils.followTrontorian != null)
        {
            Trontorian trontorian = Utils.getTrontorianByUid(int.Parse(Utils.followTrontorian.name.Replace("Minotaur", "")));
            _tileInfos.GetComponent<CanvasGroup>().alpha = 1;
            _tileInfosCasePos.text = "Joueur : #" + trontorian.uid.ToString();
            selectedTile = null;
            selectedTeam = null;
            updateCountFromPlayer(trontorian);
            return;
        }
        if (selectedTile != null)
        {
            updateCountFromTile(selectedTile);
        }
        else if (selectedTeam != null)
        {
            updateCountFromTeam(selectedTeam);
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

                if (gameObject.name.StartsWith("Minotaur"))
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
                selectedTeam = null;
                selectedTile = tile;
                _tileInfos.GetComponent<CanvasGroup>().alpha = 1;
                _tileInfosCasePos.text = "Case " + (gameObject.transform.position.x - 0.5f) + ", " + (gameObject.transform.position.z - 0.5);

                updateCountFromTile(tile);
            }
        }
    }

    public void OnTeamDropdownSelect()
    {
        if (_teamDropdown.value == 0)
            return;

        string teamName = Utils.teamNames[_teamDropdown.value - 1];

        _tileInfos.GetComponent<CanvasGroup>().alpha = 1;
        _tileInfosCasePos.text = "Equipe : " + teamName;

        selectedTile = null;
        selectedTeam = teamName;
        updateCountFromTeam(teamName);
    }

    void Update()
    {
        handleClick();
    }

    public void goBack()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex - 2);
    }
}
