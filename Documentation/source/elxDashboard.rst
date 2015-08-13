Dashboard
=========

Mac OS X
--------

- Install docker

    ::
        $ https://github.com/boot2docker/osx-installer/releases


- Install pip

    ::
        $ sudo easy_install pip

- Install docker-compose

    ::
        $ sudo pip install -U docker-compose

- Build elastix with ELASTIX_BUILD_DASHBOARD set to ON.

- To fire up the dashboard server, run the following command in the Testing/Dashboard build directory.

    ::
        $ docker-compose up

    Go to http://elastix to see the dashboard.

- Download the logstash forwarder from https://download.elastic.co/logstash-forwarder/binaries/logstash-forwarder_darwin_amd64 and run the executable with the associated configuration file

    :: 
        $ curl -O https://download.elastic.co/logstash-forwarder/binaries/logstash-forwarder_darwin_amd64
        $ chmod +x logstash-forwarder_darwin_amd64
        $ ./logstash-forwarder_darwin_amd64 -config elxLogstashForwarder.conf

- If you see "code:`DNS lookup failure "elastix": lookup elastix: no such host` add the elastix domain and associated boot2docker ip to the /etc/hosts file. For example, if :code:`$ boot2docker ip` shows you :code:`192.168.59.103`, you would the following line:

    :: 
        192.168.59.103  elastix



- We provide a key and certificate pair for testing purposes. DO NOT use this in production as they can be viewed by everybody (they are in public repository). To generate a new certificate, use the following command:

    ::
        openssl req -subj "/CN=elastix/" -x509 -batch -nodes -newkey rsa:2048 -keyout elxLogstashForwarder.key -out elxLogstashForwarder.crt

    Replace elastix with the domain name where you host the dashboard (e.g. elastix.isi.uu.nl). In production, point the ELASTIX_DASHBOARD_LOGSTASH_RSA_PRIVATE_KEY and ELASTIX_DASHBOARD_LOGSTASH_CERTIFICATE CMake variables to the new files in order for CMake to update the docker, logstash and logstash forwader configuration files with the new values. 

Docker Cheat Sheet
------------------

- To stop containers run

    ::  
        $ docker stop $(docker ps -aq)

- To delete containers run

    ::
        $ docker rm $(docker ps -aq)

- To delete images run

    :: 
        $ docker rmi $(docker ps -q)

- Bash into docker container

    ::
        $ docker exec -i -t dashboard_elastix_1 bash

    where dashboard_elastix_1 is the name of the container (could be different on your machine). Persisted data is located in the :code:`/data` directory and logs are located in the :code:`/var/log/elasticsearch`, :code:`/var/log/logstash` and :code:`/var/log/kibana` directories.