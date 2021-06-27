using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.SceneManagement;
using System;

public class EndMenu : MonoBehaviour
{

    public TextMeshProUGUI teamName;
    public RectTransform elDogitoBig;

    private bool firstCheck = false;
    // Start is called before the first frame update
    void Start()
    {
        teamName.text = Utils.winnerTeamName;
    }

    public void Wait(float seconds, Action action)
    {
        StartCoroutine(_wait(seconds, action));
    }
    IEnumerator _wait(float time, Action callback)
    {
        yield return new WaitForSeconds(time);
        callback();
    }

    // Update is called once per frame
    void Update()
    {
        if (elDogitoBig.GetComponent<CanvasGroup>().alpha > 0)
        {
            firstCheck = true;
        }
        else if (firstCheck && elDogitoBig.GetComponent<CanvasGroup>().alpha == 0)
        {
            SceneManager.LoadScene(0);
        }
    }
}
