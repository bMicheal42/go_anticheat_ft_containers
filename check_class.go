package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"path/filepath"
	"regexp"
	"strings"
)

func writeInTopFile(filesLst []string, f *os.File) {
	addline := "#include <iostream>\n#include <utility>\n#include <memory>\n#include <iterator>\n"

	for _, elem := range filesLst {
		addline += "#include \"" + elem + "\"\n"
	}

	_, err := f.WriteString(addline)
	if err != nil {
		panic(err)
	}
	scanner := bufio.NewScanner(f)

	// read the file to be appended to and output all of it
	for scanner.Scan() {
		_, err = f.WriteString(scanner.Text())
		_, err = f.WriteString("\n")
	}
	if err := scanner.Err(); err != nil {
		panic(err)
	}
	// ensure all lines are written
	f.Sync()
}

func 	searchForFiles(ext, origPath string) []string {
	var lst []string

	err := filepath.Walk(origPath,
		func(path string, info os.FileInfo, err error) error {
			if err != nil {
				return err
			}
			if filepath.Ext(path) == ext {
				lst = append(lst, path)
			}
			return nil
		})
	if err != nil {
		log.Println(err)
	}
	return lst
}

func 	getClassName(line string) string {
	split := strings.Fields(line)

	//if len(split) != 2 {
	//	return ""
	//}

	for i, elem :=range split {
		if elem == "class" {
			return split[i+1]
		}
	}
	return ""
}

func 	parseFile(fileName string) []string {
	file, err := os.Open(fileName)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	var arrClassNames []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		className := getClassName(scanner.Text())
		if className != "" {
			className = strings.Trim(className, "; :,")
			arrClassNames = append(arrClassNames, className)
		}
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
	return arrClassNames
}


func 	findClassName(arr []string, reg string) string {
	var matches []string

	for _, elem := range arr {
		lowerElem := strings.ToLower(elem)
		matched,_ := regexp.MatchString(reg, lowerElem)
		if matched {									// create array of matches e.g. "Map" "BaseMap" "MapKeyCompare"
			matches = append(matches, elem)
		}
	}
	if len(matches) == 1 {
		return matches[0]
	}

	shortest, length := "", 20							// find shortest match
	for _, elem := range matches {
		if len(elem) < length {
			shortest, length = elem, len(elem)
		}
	}
	return shortest
}

func 	main() {

// ==================================== FIND ALL .hpp FILES IN DIRECTORY ===============================================
	var arrayNoTests 	[]string
	var arrayNoTrash 	[]string
	var classArray 		[]string

	array := searchForFiles(".hpp", ".") 			// all fils in arr

	for _, elem := range array {								// delete all test headers
		lowerElem 		:= strings.ToLower(elem)
		matchedTest,_ 	:= regexp.MatchString(`test`, lowerElem)
		if !matchedTest {
			arrayNoTests = append(arrayNoTests, elem)
		}
	}

	for _, elem := range arrayNoTests {								// delete all test headers
		lowerElem 		:= strings.ToLower(elem)
		matchedIt,_ 	:= regexp.MatchString(`it`, lowerElem)
		if !matchedIt {
			arrayNoTrash = append(arrayNoTrash, elem)
		}
	}
// ====================================== PARSE CLASS NAMES in FILES ===================================================
	for _, elem := range arrayNoTrash {
		if ret := parseFile(elem); ret != nil {
			classArray = append(classArray, ret...)
		}
	}

// ================================================ TEST ===============================================================
	//TEST TODO delete this
	//var TestArr []string
	//TestArr = append(TestArr,  "class_Mo P", "VEC_tor", "list_it", "map_ITERATOR", "lIST_iter","LisT_ramzI", "it_vector", "queueu", "stak")

// ======================================== DELETE ALL ITER CLASS NAMES ================================================
	var classArray_no_it []string
	for _, elem := range classArray {
		lowerElem := strings.ToLower(elem)
		matched,_ := regexp.MatchString(`it`, lowerElem)

		if !matched {
			classArray_no_it = append(classArray_no_it, elem)
		}
	}

// ===================================== FIND PEERs CLASS NAMES ========================================================
	list_class 		:= findClassName(classArray_no_it, "list")
	map_class 		:= findClassName(classArray_no_it, "map")
	vector_class 	:= findClassName(classArray_no_it, "vec")
	queue_class 	:= findClassName(classArray_no_it, "queu")
	stack_class 	:= findClassName(classArray_no_it, "sta")

// ========================================== CREATE NEW MAIN ==========================================================
	file, err := os.Open("BM_main.cpp")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	f, e := os.Create("BM_main_new.cpp")
	if e != nil {
		panic(e)
	}
	writeInTopFile(arrayNoTests, f) // add all includes from project to our main

	defer f.Close()

	scanner := bufio.NewScanner(file)
	var currentLine string
	for scanner.Scan() {
		currentLine = scanner.Text()
		re := regexp.MustCompile(`ft::(.*?)<`)
		submatchall := re.FindAllString(scanner.Text(), -1)
		for _, element := range submatchall {
			element = strings.Trim(element, "ft::")
			element = strings.Trim(element, "<")
			if element == "list" {
				re := regexp.MustCompile(`list`)
				currentLine = re.ReplaceAllString(scanner.Text(), list_class)
			} else if element == "vector" {
				re := regexp.MustCompile(`vector`)
				currentLine = re.ReplaceAllString(scanner.Text(), vector_class)
			} else if element == "map" {
				re := regexp.MustCompile(`map`)
				currentLine = re.ReplaceAllString(scanner.Text(), map_class)
			} else if element == "queue" {
				re := regexp.MustCompile(`queue`)
				currentLine = re.ReplaceAllString(scanner.Text(), queue_class)
			} else if element == "stack" {
				re := regexp.MustCompile(`stack`)
				currentLine = re.ReplaceAllString(scanner.Text(), stack_class)
			}
		}
		fmt.Fprintln(f, currentLine)
	}
}