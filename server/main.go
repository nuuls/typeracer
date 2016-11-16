package main

import (
	"io/ioutil"
	"net/http"
	"os/exec"
	"regexp"
	"time"

	"github.com/nuuls/log"
)

func main() {
	log.AddLogger(log.DefaultLogger)
	http.HandleFunc("/", simulateKeyboard)
	log.Fatal(http.ListenAndServe(":8181", nil))
}

func simulateKeyboard(w http.ResponseWriter, r *http.Request) {
	bs, err := ioutil.ReadAll(r.Body)
	if err != nil {
		log.Error(err)
		w.WriteHeader(400)
		return
	}
	log.Debug(string(bs))
	cmd := exec.Command("./test.exe", getText(string(bs)))
	time.Sleep(time.Second)
	res, err := cmd.CombinedOutput()
	log.Info(string(res))
	if err != nil {
		log.Critical(err)
		w.WriteHeader(500)
		return
	}
	w.WriteHeader(200)
}

var re = regexp.MustCompile(`>([\w\'\"-]+)<.+> (.+)<`)

func getText(data string) string {
	matches := re.FindStringSubmatch(data)
	if len(matches) < 3 {
		log.Warning("no text found in", data)
		return ""
	}
	return matches[1] + " " + matches[2]
}
