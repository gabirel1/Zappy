using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.SceneManagement;
using System;

public class EndMenu : MonoBehaviour
{

    public TextMeshProUGUI teamName;
    public GameObject animationGameObject;
    public RectTransform elDogitoBig;
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
        if (animationGameObject.GetComponent<CanvasGroup>().alpha == 0)
        {
            if (elDogitoBig.GetComponent<CanvasGroup>().alpha < 1)
            {
                elDogitoBig.GetComponent<CanvasGroup>().alpha += 0.01f;
            }
            else
            {
                Wait(3, () => {
                    SceneManager.LoadScene(0);
                });
            }
        }
        else if (animationGameObject.transform.position.y > 2370)
        {
            animationGameObject.GetComponent<CanvasGroup>().alpha -= 0.01f;
        }
    }
}
