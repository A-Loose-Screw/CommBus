#ifndef COMMBUS_COMMON_H
#define COMMBUS_COMMON_H

/**
 * @brief Common stringifies
 * 
 */
#ifndef COMMBUS_STRINGIFY
#define COMMBUS_STRINGIFY(x) #x
#endif

#ifndef COMMBUS_TOSTRING
#define COMMBUS_TOSTRING(x) COMMBUS_STRINGIFY(x)
#endif

#ifndef COMMBUS_ADDR_PORT
#define COMMBUS_ADDR_PORT 1905
#endif

#ifndef COMMBUS_LOCAL_ADDR_IP
#define COMMBUS_LOCAL_ADDR_IP "tcp://0.0.0.0"
#endif

/**
 * @brief Used primarily for servers who need to bind to the local address 0.0.0.0
 * 
 */
#ifndef COMMBUS_LOCAL_ADDR
#define COMMBUS_LOCAL_ADDR COMMBUS_LOCAL_ADDR_IP ":" COMMBUS_TOSTRING(COMMBUS_ADDR_PORT)
#endif


/**
 * @brief Used for nodes connecting to server with ip. expands to "tcp://<insert_address>:1905"
 * 
 */
#ifndef COMMBUS_GET_EXTERNAL_IP
#define COMMBUS_GET_EXTERNAL_IP(ip) "tcp://" ip ":" COMMBUS_TOSTRING(COMMBUS_ADDR_PORT)
#endif

#endif