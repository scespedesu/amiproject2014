//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "RoutingTablesConf.h"

#include "MobilityAccess.h"
#include "IPvXAddressResolver.h"
#include "IInterfaceTable.h"
#include "IPv4InterfaceData.h"
#include "StationaryMobility.h"
#include "AppLayer.h"

RoutingTablesConf::RoutingTablesConf() {
    // TODO Auto-generated constructor stub
    reStart();

}

void RoutingTablesConf::reStart()
{
    // TODO Auto-generated constructor stub
    // fill in routing tables with static routes
    cTopology topo("topo");
    topo.extractByProperty("node");

    cModule *mod = dynamic_cast<cModule*> (getOwner());

    for (mod = dynamic_cast<cModule*> (getOwner())->getParentModule(); mod != 0; mod = mod->getParentModule())
    {
            cProperties *properties = mod->getProperties();
            if (properties && properties->getAsBool("node"))
                break;
    }
    vectorList.clear();
    routeCache.clear();
    linkCache.clear();
    routeCacheIp.clear();

    int numberOfNodes = topo.getNumNodes();

    for (int i = 0; i < numberOfNodes; i++)
    {
        cTopology::Node *destNode = topo.getNode(i);
        if(destNode==NULL){
            opp_error("node not found");
        }

     //   IMobility *mod;

      //   IMobility * mod = dynamic_cast<IMobility*>(destNode->getModule());
        IMobility * mod = dynamic_cast<IMobility*>(destNode->getModule()->getSubmodule("mobility"));
    //   StationaryMobility * mod = dynamic_cast<StationaryMobility*>(destNode->getModule());
        if (mod == NULL)
           opp_error("node or mobility module not found");
        nodeInfo info;
        info.mob = mod;
        //info.itable = IPvXAddressResolver().findInterfaceTableOf(destNode->getModule());
        info.itable = IPvXAddressResolver().findInterfaceTableOf(destNode->getModule());

        vectorList.push_back(info);

        int numInterfaces=vectorList[i].itable->getNumInterfaces();
//
//        InterfaceEntry *e = vectorList[i].itable->getInterface(j);
//
//                   if (e->getMACAddress().isUnspecified())
//                       continue;
//                   if (e->isLoopback())
//                       continue;
//                   related[e->getMACAddress()] = i;
//                  // EV<<"Valor de la MAC actual: "<<e->getMACAddress().str() <<" \n";
//
//                   IPv4Address adr = e->ipv4Data()->getIPAddress();
//                          if (!adr.isUnspecified())
//                              relatedIp [adr] = i;


        for (int j = 0 ; j < numInterfaces; j++)
        {

            InterfaceEntry *e = vectorList[i].itable->getInterface(j);
            if (e->getMacAddress().isUnspecified())
                continue;
            if (e->isLoopback())
                continue;
            related[e->getMacAddress()] = i;
            EV<<"MAC del nodo "<<i<< " : "<<e->getMacAddress().str() <<" \n";
            EV<<"IP del nodo "<<i<< " : "<<e->ipv4Data()->getIPAddress().str() <<" \n";
            IPv4Address adr = e->ipv4Data()->getIPAddress();
                   if (!adr.isUnspecified())
                       relatedIp [adr] = i;
                   else
                       opp_error("IP address is not specified");

                //   EV<<"Valor de la IP actual: "<<e->ipv4Data()->getIPAddress().str() <<" \n";

        }

    }

}

RoutingTablesConf::~RoutingTablesConf()
{
    // TODO Auto-generated destructor stub
    cleanLinkArray();
    vectorList.clear();
    routeCache.clear();
    linkCache.clear();
    routeCacheIp.clear();

}

void RoutingTablesConf::fillRoutingTables(const double &tDistance)
{
    // fill in routing tables with static routes
    LinkCache templinkCache;
    // first find root node connections
    Coord cRoot = vectorList[rootNode].mob->getCurrentPosition();
    for (int i=0; i< (int)vectorList.size(); i++)
    {
        if (i == rootNode)
            continue;
        Coord ci = vectorList[i].mob->getCurrentPosition();
        if (cRoot.distance(ci) <= tDistance)
        {
            templinkCache.insert(LinkPair(rootNode,i));
        }
    }
    if (templinkCache.empty())
    {
        // root node doesn't have connections
        linkCache.clear();
        routeCache.clear();
        routeMap.clear();
        routeCacheIp.clear();
        cleanLinkArray();
        return;
    }

    for (int i=0; i< (int)vectorList.size(); i++)
    {
        if (i == rootNode)
            continue;
        for (int j = i; j < (int)vectorList.size(); j++)
        {
            if (i == j)
                continue;
            if (j == rootNode)
                continue;
            Coord ci = vectorList[i].mob->getCurrentPosition();
            Coord cj = vectorList[j].mob->getCurrentPosition();
            if (ci.distance(cj) <= tDistance)
            {
                templinkCache.insert(LinkPair(i,j));
            }
        }
    }

    if (linkCache == templinkCache)
    {
        return;
    }

    linkCache = templinkCache;
    routeCache.clear();
    routeMap.clear();
    routeCacheIp.clear();
    // clean edges
    cleanLinkArray();
    for (LinkCache::iterator it = linkCache.begin(); it != linkCache.end(); ++it)
    {
        addEdge ((*it).node1, (*it).node2,1);
        addEdge ((*it).node2, (*it).node1,1);
    }
}


RoutingTablesConf::DijkstraShortest::State::State()
{
    idPrev = -1;
    label=tent;
}

RoutingTablesConf::DijkstraShortest::State::State(const unsigned int  &costData)
{
    idPrev=-1;
    label=tent;
    cost = costData;
}


void RoutingTablesConf::DijkstraShortest::State::setCostVector(const unsigned int &costData)
{
    cost=costData;
}

void RoutingTablesConf::cleanLinkArray()
{
    for (LinkArray::iterator it=linkArray.begin();it!=linkArray.end();it++)
        while (!it->second.empty())
        {
            delete it->second.back();
            it->second.pop_back();
        }
    linkArray.clear();
}

void RoutingTablesConf::addEdge (const int & originNode, const int & last_node,unsigned int cost)
{
    LinkArray::iterator it;
    it = linkArray.find(originNode);
    if (it!=linkArray.end())
    {
         for (unsigned int i=0;i<it->second.size();i++)
         {
             if (last_node == it->second[i]->last_node_)
             {
                  it->second[i]->cost =cost;
                  return;
             }
         }
    }
    RoutingTablesConf::DijkstraShortest::Edge *link = new RoutingTablesConf::DijkstraShortest::Edge;
    // The last hop is the interface in which we have this neighbor...
    link->last_node_ = last_node;
    // Also record the link delay and quality..
    link->cost = cost;
    linkArray[originNode].push_back(link);
}

int RoutingTablesConf::getIdNode(const MACAddress &add)
{
    std::map<MACAddress,int>::iterator it = related.find(add);
    if (it != related.end())
        return it->second;
    opp_error("Node not found with MAC Address %s",add.str().c_str());
    return -1;
}

int RoutingTablesConf::getIdNode(const IPv4Address &add)
{
    std::map<IPv4Address,int>::iterator it = relatedIp.find(add);
    if (it != relatedIp.end())
        return it->second;
    int numDireccionesIp =  relatedIp.size();
    int numNodeinfo = vectorList.size();
    const char *dirIpNodeCero =  vectorList[0].itable->getInterface(0)->ipv4Data()->getIPAddress().str().c_str();
    opp_error("Node not found with IP Address %s", add.str().c_str());
    return -1;
}

void RoutingTablesConf::setRoot(const int & dest_node)
{
    rootNode = dest_node;
}


void RoutingTablesConf::run()
{
    std::multiset<RoutingTablesConf::DijkstraShortest::SetElem> heap;
    routeMap.clear();
    if (linkArray.empty())
        return;

    LinkArray::iterator it;
    it = linkArray.find(rootNode);
    if (it==linkArray.end())
        opp_error("Node root not found %i",rootNode);
    RoutingTablesConf::DijkstraShortest::State state(0);
    state.label = tent;
    routeMap[rootNode] = state;


    RoutingTablesConf::DijkstraShortest::SetElem elem;
    elem.iD = rootNode;
    elem.cost= 0;
    heap.insert(elem);

    while (!heap.empty())
    {
        RoutingTablesConf::DijkstraShortest::SetElem elem = *heap.begin();
        heap.erase(heap.begin());

        RouteMap::iterator it;

        it = routeMap.find(elem.iD);
        if (it==routeMap.end())
            opp_error("node not found in routeMap %i",elem.iD);
        if ((it->second).label == perm)
            continue;

        (it->second).label = perm;

        LinkArray::iterator linkIt=linkArray.find(elem.iD);

        for (unsigned int i=0;i<linkIt->second.size();i++)
        {
            RoutingTablesConf::DijkstraShortest::Edge* current_edge= (linkIt->second)[i];
            RouteMap::iterator itNext = routeMap.find(current_edge->last_node_);
            if (itNext != routeMap.end() && itNext->second.label == perm)
                continue;
            unsigned int cost = current_edge->cost + (it->second).cost;

            if (current_edge->last_node_ == 113)
                EV << "destino \n";
            if (itNext == routeMap.end())
            {
                RoutingTablesConf::DijkstraShortest::State state;
                state.idPrev = elem.iD;
                state.cost = cost;
                state.label = tent;
                routeMap[current_edge->last_node_] = state;
                RoutingTablesConf::DijkstraShortest::SetElem newElem;
                newElem.iD = current_edge->last_node_;
                newElem.cost = cost;
                heap.insert(newElem);
            }
            else
            {
                if (cost < itNext->second.cost)
                {
                    itNext->second.cost = cost;
                    itNext->second.idPrev = elem.iD;
                    // actualize heap
                    RoutingTablesConf::DijkstraShortest::SetElem newElem;
                    newElem.iD=current_edge->last_node_;
                    newElem.cost = cost;
                    heap.insert(newElem);
                }
            }
        }
    }
}


void RoutingTablesConf::runUntil (const int &target)
{
    std::multiset<RoutingTablesConf::DijkstraShortest::SetElem> heap;
    routeMap.clear();

    if (linkArray.empty())
        return;

    LinkArray::iterator it;
    it = linkArray.find(rootNode);
    if (it==linkArray.end())
        opp_error("Root node not found %i",rootNode);
    RoutingTablesConf::DijkstraShortest::State state(0);
    state.label = tent;
    routeMap[rootNode] = state;


    RoutingTablesConf::DijkstraShortest::SetElem elem;
    elem.iD = rootNode;
    elem.cost= 0;
    heap.insert(elem);

    while (!heap.empty())
    {
        RoutingTablesConf::DijkstraShortest::SetElem elem=*heap.begin();
        heap.erase(heap.begin());

        RouteMap::iterator it;

        it = routeMap.find(elem.iD);
        if (it==routeMap.end())
            opp_error("node not found in routeMap %i",elem.iD);
        if ((it->second).label == perm)
            continue;
        (it->second).label = perm;
        if (target == elem.iD)
            return;

        LinkArray::iterator linkIt=linkArray.find(elem.iD);

        for (unsigned int i=0;i<linkIt->second.size();i++)
        {
            RoutingTablesConf::DijkstraShortest::Edge* current_edge= (linkIt->second)[i];
            RouteMap::iterator itNext = routeMap.find(current_edge->last_node_);
            unsigned int cost = current_edge->cost + (it->second).cost;
            if (itNext == routeMap.end())
            {
                RoutingTablesConf::DijkstraShortest::State state;
                state.idPrev=elem.iD;
                state.cost=cost;
                state.label = tent;
                routeMap[current_edge->last_node_] = state;
                RoutingTablesConf::DijkstraShortest::SetElem newElem;
                newElem.iD=current_edge->last_node_;
                newElem.cost = cost;
                heap.insert(newElem);
            }
            else
            {
                if (itNext->second.label == perm)
                    continue;
                if ( cost < itNext->second.cost)
                {
                    itNext->second.cost = cost;
                    itNext->second.idPrev = elem.iD;
                    // actualize heap
                    RoutingTablesConf::DijkstraShortest::SetElem newElem;
                    newElem.iD=current_edge->last_node_;
                    newElem.cost = cost;
                    heap.insert(newElem);
                }
            }
        }
    }
}


bool RoutingTablesConf::getRoute(const int &nodeId,std::vector<int> &pathNode)
{
    RouteMap::iterator it = routeMap.find(nodeId);
    if (it==routeMap.end())
        return false;

    std::vector<int> path;
    int currentNode = nodeId;
    pathNode.clear();
    while (currentNode!=rootNode)
    {
        pathNode.push_back(currentNode);
        currentNode = it->second.idPrev;
        it = routeMap.find(currentNode);
        if (it==routeMap.end())
            opp_error("error in data routeMap");
    }
    return true;
}


bool RoutingTablesConf::findRoute(const double &coverageArea, const int &nodeId,std::vector<int> &pathNode)
{
    std::vector<int> route;
    if (getRoute(nodeId,pathNode))
        return true;
    else
    {
        run();
        if (getRoute(nodeId,pathNode))
             return true;
    }
    return false;
}

bool RoutingTablesConf::findRoute(const double &coverageArea, const MACAddress &dest,std::vector<MACAddress> &pathNode)
{
    fillRoutingTables(coverageArea);

    RouteCache::iterator it = routeCache.find(dest);
    if (it!=routeCache.end())
    {
        pathNode = it->second;
        return true;
    }

    std::vector<int> route;
    int nodeId = getIdNode(dest);
    if (findRoute(coverageArea, nodeId, route))
    {
        std::vector<MACAddress> path;
        for (unsigned int i = 0; i < route.size(); i++)
        {
            for (std::map<MACAddress,int>::iterator it2 = related.begin(); it2 != related.end(); ++it2)
            {
                if (it2->second ==  route[i])
                    path.push_back(it2->first);
            }
        }
        if (path.size() != route.size())
        {
            opp_error("node id not found");
        }
        pathNode = path;
        // include path in the cache
        routeCache[dest] = path;
        return true;
    }
    return false;
}


bool RoutingTablesConf::findRoute(const double &coverageArea, const IPv4Address &dest,std::vector<IPv4Address> &pathNode)
{
    fillRoutingTables(coverageArea);

    RouteCacheIp::iterator it = routeCacheIp.find(dest);
    if (it!=routeCacheIp.end())
    {
        pathNode = it->second;
        return true;
    }

    std::vector<int> route;
    int nodeId = getIdNode(dest);
    if (findRoute(coverageArea, nodeId, route))
    {
        std::vector<IPv4Address> path;
        for (unsigned int i = 0; i < route.size(); i++)
        {
            for (std::map<IPv4Address,int>::iterator it2 = relatedIp.begin(); it2 != relatedIp.end(); ++it2)
            {
                if (it2->second ==  route[i])
                    path.push_back(it2->first);
            }
        }
        if (path.size() != route.size())
        {
            opp_error("node id not found");
        }
        // include path in the cache
        pathNode = path;
        routeCacheIp[dest] = path;
        return true;
    }
    return false;
}

Coord RoutingTablesConf::getPos(const int &node)
{
    return vectorList[node].mob->getCurrentPosition();
}

void RoutingTablesConf::getNeighbours(const IPv4Address &node, std::vector<IPv4Address>&list, const double &distance)
{
    list.clear();
    int nodeId =  getIdNode(node);
    Coord pos = vectorList[nodeId].mob->getCurrentPosition();
    for (int i = 0; i < (int)vectorList.size(); i++)
    {
        if (i == nodeId)
            continue;
        if (pos.distance(vectorList[i].mob->getCurrentPosition()) < distance)
        {
            for (std::map<IPv4Address,int>::iterator it2 = relatedIp.begin(); it2 != relatedIp.end(); ++it2)
            {
                if (it2->second ==  i)
                    list.push_back(it2->first);
            }
        }
    }
}

MACAddress RoutingTablesConf::getMACAddressFromID(const int id){

    for (std::map<MACAddress,int>::iterator it2 = related.begin(); it2 != related.end(); ++it2)
                {
                    if (it2->second == id)
                        return it2->first;
                }

}

void RoutingTablesConf::getNeighbours(const MACAddress &node, std::vector<MACAddress>& list, const double &distance)
{
    list.clear();

    list.clear();
    int nodeId =  getIdNode(node);
    Coord pos = vectorList[nodeId].mob->getCurrentPosition();
    for (int i = 0; i < (int)vectorList.size(); i++)
    {
        if (i == nodeId)
            continue;
        if (pos.distance(vectorList[i].mob->getCurrentPosition()) < distance)
        {
            for (std::map<MACAddress,int>::iterator it2 = related.begin(); it2 != related.end(); ++it2)
            {
                if (it2->second ==  i)
                    list.push_back(it2->first);
            }
        }
    }
}



