#!/bin/sh

apt list | grep installed | grep zesty | awk -F "," '{print $1}'
