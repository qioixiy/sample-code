package main

import (
	"log"
	"net/http"
)

func main() {
	// Simple static webserver:
	log.Fatal(http.ListenAndServe(":8088", http.FileServer(http.Dir("/home/qioixiy"))))
}
