package main

import (
	"fmt"
	"log"

	"example.com/greetings"
)

func main() {
	log.SetPrefix("greetings: ")
	log.SetFlags(0)

	// A slice of names
	names := []string{"ffej", "nifty", "gopher"}

	messages, err := greetings.Hellos(names)
	if err != nil {
		log.Fatal(err)
	}
	for name, message := range messages {
		fmt.Println(name, message)
	}
}

// https://go.dev/doc/tutorial/add-a-test