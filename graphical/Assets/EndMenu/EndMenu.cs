using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class EndMenu : MonoBehaviour
{

    public TextMeshProUGUI _teamName;

    public 
    // Start is called before the first frame update
    void Start()
    {
        _teamName.text = Utils.winnerTeamName;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
