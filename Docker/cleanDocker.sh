#!/bin/bash
docker-compose down -v
docker rmi -f $(docker images -a -q)
docker volume rm $(docker volume ls -q)
docker rm -f $(docker ps -a -q)

# remove bots_ok to regenerate both images
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
rm -rf $parent_path/../Server/bots_ok

echo "Docker env is cleaned!"
