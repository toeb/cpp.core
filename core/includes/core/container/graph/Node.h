/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#pragma once
#include <core/core.h>

#include <core/patterns/Derivable.h>
#include <core/container/Set.h>
#include <core/template/Comparator.h>

NS_BEGIN(CORE_NAMESPACE)

  /**
   * \brief Node.
   */
  template<typename Derived>
  class Node : public Derivable<Derived>, public ObservableCollection<Derived*>, public ObservableCollection<Derived*>::Observer {
private:

    /**
     * \brief The predecessors.
     */
    Set<Derived*> _predecessors;

    /**
     * \brief The successors.
     */
    Set<Derived*> _successors;
public:

    /**
     * \brief Default constructor.
     */
    Node();

    /**
     * \brief Destructor. removes all successors and predecessors
     */
    virtual ~Node();

    /**
     * \brief callback when an element is added to the node. makes sure that the nodes are connected in
     *        both directions.
     *
     * \param [in,out]  sender  If non-null, the sender.
     * \param [in,out]  node    If non-null, the node.
     */
    void elementAdded(ObservableCollection<Derived*> * sender, Derived * node);

    /**
     * \brief callback when an element is removed from the node. makes sure the nodes are removed.
     *
     * \param [in,out]  sender  If non-null, the sender.
     * \param [in,out]  node    If non-null, the node.
     */
    void elementRemoved(ObservableCollection<Derived*> * sender, Derived * node);

    /**
     * \brief all connected nodes (union of predecessors and successors)
     *
     * \return  null if it fails, else.
     */
    Set<Derived*> neighbors() const;

    /**
     * \brief read access to predecessors.
     *
     * \return  null if it fails, else.
     */
    const Set<Derived*> & predecessors() const;

    /**
     * \brief read write access to predecessors.
     *
     * \return  null if it fails, else.
     */
    Set<Derived*> & predecessors();

    /**
     * \brief read write access to successor by index.
     *
     * \param i Zero-based index of the.
     *
     * \return  null if it fails, else.
     */
    Derived * successor(size_t i);

    /**
     * \brief read access to successor by index.
     *
     * \param i Zero-based index of the.
     *
     * \return  null if it fails, else.
     */
    const Derived * successor(size_t i) const;

    /**
     * \brief read / write access to predecessor by index.
     *
     * \param i Zero-based index of the.
     *
     * \return  null if it fails, else.
     */
    Derived * predecessor(size_t i);

    /**
     * \brief read access to predecessor by index.
     *
     * \param i Zero-based index of the.
     *
     * \return  null if it fails, else.
     */
    const Derived * predecessor(size_t i) const;

    /**
     * \brief read access tot first successor.
     *
     * \return  null if it fails, else.
     */
    const Derived * firstSuccessor() const;

    /**
     * \brief read write access to first successor.
     *
     * \return  null if it fails, else.
     */
    Derived * firstSuccessor();

    /**
     * \brief returns the first predecessor (const)
     *
     * \return  null if it fails, else.
     */
    const Derived * firstPredecessor() const;

    /**
     * \brief returns the first predecessor.
     *
     * \return  null if it fails, else.
     */
    Derived * firstPredecessor();

    /**
     * \brief allows const access to the successors.
     *
     * \return  null if it fails, else.
     */
    const Set<Derived*> & successors() const;

    /**
     * \brief allows access to the successors.
     *
     * \return  null if it fails, else.
     */
    Set<Derived*> & successors();

    /**
     * \brief adds a set of predecessors (arrows indicate direction of connection.
     *
     * \param nodes The nodes.
     *
     * \return  The shifted result.
     */
    Derived & operator <<(const Set<Derived*> &nodes);

    /**
     * \brief adds a set of successors.
     *
     * \param nodes The nodes.
     *
     * \return  The shifted result.
     */
    Derived & operator >>(const Set<Derived*> &nodes);

    /**
     * \brief adds a single predecessor.
     *
     * \param [in,out]  node  The node.
     *
     * \return  The shifted result.
     */
    Derived & operator <<(Derived & node);

    /**
     * \brief adds a single successor.
     *
     * \param [in,out]  node  The node.
     *
     * \return  The shifted result.
     */
    Derived & operator >>(Derived & node);

    /**
     * \brief adds a single predecessor (by pointer)
     *
     * \param [in,out]  node  If non-null, the node.
     *
     * \return  The shifted result.
     */
    Derived & operator <<(Derived * node);

    /**
     * \brief adds a single successor (by pointer)
     *
     * \param [in,out]  node  If non-null, the node.
     *
     * \return  The shifted result.
     */
    Derived & operator >>(Derived * node);

    /**
     * \brief removes the node from successors and predecessors.
     *
     * \param [in,out]  node  If non-null, the node to remove.
     */
    void remove(Derived * node);

    /**
     * \brief iterates the neighbors.
     *
     * \param [in,out]  action  If non-null, the action.
     */
    void foreachNeighbor(std::function<void (Derived*)> action) const;

    /**
     * \brief iterates the predecessors.
     *
     * \param [in,out]  action  If non-null, the action.
     */
    void foreachPredecessor(std::function<void (Derived*)> action) const;

    /**
     * \brief iterates the successors.
     *
     * \param [in,out]  action  If non-null, the action.
     */
    void foreachSuccessor(std::function<void (Derived*)> action) const;

    /**
     * \brief does a depth first search calling action on every node and also passing the path to the
     *        node as a parameter to action.
     *
     * \param [in,out]  action  If non-null, the action.
     * \param currentpath       (optional) [in,out] If non-null, the currentpath.
     */
    void dfsWithPath(std::function<void (Derived *, Set<Derived * > )> action, Set<Derived * > currentpath = Set<Derived*>());

    /**
     * \brief Dfs the given action.
     *
     * \param [in,out]  action  If non-null, the action.
     */
    void dfs(std::function<void (Derived * )> action);

    /**
     * \brief really bad implementation of dfs, it is slow and will crash (stack overflow ) if there
     *        are cycles in the graph.
     *
     * \param [in,out]  f [in,out] If non-null, the std::function&lt;void(bool&amp;,Derived*)&gt; to
     *                    process.
     * \param successors  The successors.
     */
    void dfs(std::function<void (bool &, Derived *)> f, std::function<void (Set<Derived*> &, const Derived &) > successors);

    /**
     * \brief also a realy bad implemention. this time of bfs (performancewise). it does not crash if
     *        cycles are contained and returns the number of cycles found.
     *
     * \param [in,out]  f [in,out] If non-null, the std::function&lt;void(bool&amp;,Derived*)&gt; to
     *                    process.
     * \param successors  The successors.
     *
     * \return  .
     */
    int bfs(std::function<void (bool&,Derived*)> f,std::function<void (Set<Derived*> &, const Derived &) > successors);

    /**
     * \brief overload.
     *
     * \param [in,out]  f [in,out] If non-null, the std::function&lt;void(bool&amp;,Derived*)&gt; to
     *                    process.
     *
     * \return  .
     */
    int bfs(std::function<void (bool&,Derived*)> f);

    /**
     * \brief Executes the predecessor added action.
     *
     * \param [in,out]  predecessor If non-null, the predecessor.
     */
    virtual void onPredecessorAdded(Derived * predecessor){}

    /**
     * \brief Executes the successor added action.
     *
     * \param [in,out]  successor If non-null, the successor.
     */
    virtual void onSuccessorAdded(Derived * successor){}

    /**
     * \brief Executes the predecessor removed action.
     *
     * \param [in,out]  predecessor If non-null, the predecessor.
     */
    virtual void onPredecessorRemoved(Derived* predecessor){}

    /**
     * \brief Executes the successor removed action.
     *
     * \param [in,out]  predecessor If non-null, the predecessor.
     */
    virtual void onSuccessorRemoved(Derived * predecessor){}
  };

  // implementation of node

  template<typename Derived>
  void Node<Derived>::remove(Derived * node){
    successors()/=node; predecessors()/=node;
  }

  template<typename Derived>
  void Node<Derived>::foreachNeighbor(std::function<void (Derived*)> action) const {
    neighbors().foreachElement(action);
  }
  template<typename Derived>
  void Node<Derived>::foreachPredecessor(std::function<void (Derived*)> action) const {
    predecessors().foreachElement(action);
  }
  template<typename Derived>
  void Node<Derived>::foreachSuccessor(std::function<void (Derived*)> action) const {
    successors().foreachElement(action);
  }

  template<typename Derived>
  Node<Derived>::Node():
    Derivable<Derived>(static_cast<typename Derivable<Derived>::derived_ptr>(this))
  {
    _predecessors.addObserver(this);
    _successors.addObserver(this);
  }
  template<typename Derived>
  Node<Derived>::~Node(){
    _predecessors.clear();
    _successors.clear();
  }
  // callback when an element is added to the node. makes sure that the nodes are connected in both directions
  template<typename Derived>
  void Node<Derived>::elementAdded(ObservableCollection<Derived*> * sender, Derived * node){
    if(sender==&_predecessors) {
      onPredecessorAdded(node);
      node->successors() |= this->derived();
    }
    if(sender==&_successors) {
      onSuccessorAdded(node);
      node->predecessors()|=this->derived();
    }
  }
  // callback when an element is removed from the node. makes sure the nodes are removed
  template<typename Derived>
  void Node<Derived>::elementRemoved(ObservableCollection<Derived*> * sender, Derived * node){
    if(sender==&_predecessors) {
      onPredecessorRemoved(node);
      node->successors() /=this->derived();
    }
    if(sender==&_successors) {
      onSuccessorRemoved(node);
      node->predecessors()/=this->derived();
    }
  }
  // all connected nodes (union of predecessors and successors)
  template<typename Derived>
  Set<Derived*> Node<Derived>::neighbors() const {
    return predecessors()|successors();
  }
  // read access to predecessors
  template<typename Derived>
  const Set<Derived*> & Node<Derived>::predecessors() const {
    return _predecessors;
  }
  // read write access to predecessors
  template<typename Derived>
  Set<Derived*> & Node<Derived>::predecessors(){
    return _predecessors;
  }
  // read write access to successor by index
  template<typename Derived>
  Derived * Node<Derived>::successor(size_t i){
    return successors().at(i);
  }
  // read access to successor by index
  template<typename Derived>
  const Derived * Node<Derived>::successor(size_t i) const {
    return successors().at(i);
  }
  //read / write access to predecessor by index
  template<typename Derived>
  Derived * Node<Derived>::predecessor(size_t i){
    return predecessors().at(i);
  }
  // read access to predecessor by index
  template<typename Derived>
  const Derived * Node<Derived>::predecessor(size_t i) const {
    return predecessors().at(i);
  }
  // read access tot first successor
  template<typename Derived>
  const Derived * Node<Derived>::firstSuccessor() const {
    return successors().first();
  }
  //read write access to first successor
  template<typename Derived>
  Derived * Node<Derived>::firstSuccessor(){
    return successors().first();
  }
  // returns the first predecessor (const)
  template<typename Derived>
  const Derived * Node<Derived>::firstPredecessor() const {
    return predecessors().first();
  }
  // returns the first predecessor
  template<typename Derived>
  Derived * Node<Derived>::firstPredecessor(){
    return predecessors().first();
  }
  // allows const access to the successors
  template<typename Derived>
  const Set<Derived*> & Node<Derived>::successors() const {
    return _successors;
  }
  //allows access to the successors
  template<typename Derived>
  Set<Derived*> & Node<Derived>::successors(){
    return _successors;
  }

  // adds a set of predecessors (arrows indicate direction of connection
  template<typename Derived>
  Derived & Node<Derived>::operator <<(const Set<Derived*> &nodes){
    predecessors() |= nodes;
    return *(this->derived());
  }
  // adds a set of successors
  template<typename Derived>
  Derived & Node<Derived>::operator >>(const Set<Derived*> &nodes){
    successors() |= nodes;
    return *(this->derived());
  }
  // adds a single predecessor
  template<typename Derived>
  Derived & Node<Derived>::operator <<(Derived & node){
    predecessors().add(&node);
    return *(this->derived());
  }
  //adds a single successor
  template<typename Derived>
  Derived & Node<Derived>::operator >>(Derived & node){
    successors().add(&node);
    return *(this->derived());
  }
  // adds a single predecessor (by pointer)
  template<typename Derived>
  Derived & Node<Derived>::operator <<(Derived * node){
    predecessors().add(node);
    return *(this->derived());
  }
  // adds a single successor (by pointer)
  template<typename Derived>
  Derived & Node<Derived>::operator >>(Derived * node){
    successors().add(node);
    return *(this->derived());
  }

  template<typename Derived>
  void Node<Derived>::dfsWithPath(std::function<void (Derived *, Set<Derived * > )> action, Set<Derived * > currentpath){
    action(this->derived(),currentpath);
    successors().foreachElement([action,this,&currentpath](Derived * next){
                                  next->dfsWithPath(action,currentpath|this->derived());
                                });
  }

  template<typename Derived>
  void Node<Derived>::dfs(std::function<void (Derived * )> action){
    auto a = [action](bool& b, Derived * d){action(d); };
    auto b = [] (Set<Derived * > &successors, const Derived &current){successors |= current.successors(); };
    dfs(a,b );
  }

  // really bad implementation of dfs, it is slow and will crash (stack overflow ) if there are cycles in the graph
  template<typename Derived>
  void Node<Derived>::dfs(std::function<void (bool &, Derived *)> f, std::function<void (Set<Derived*> &, const Derived &) > successors){
    Set<Derived* > next;
    successors(next, *(this->derived()));
    bool cont=true;
    f(cont,this->derived());
    if(!cont) return;
    next.foreachElement([f,successors](Derived * n){
                          n->dfs(f,successors);
                        });
  }

  // also a realy bad implemention. this time of bfs (performancewise). it does not crash if cycles are contained and returns the number of cycles found
  template<typename Derived>
  int Node<Derived>::bfs(std::function<void (bool&,Derived*)> f,std::function<void (Set<Derived*> &, const Derived &) > successors){
    Set<Derived *> list = this->derived();
    int cycles =0;
    while(list) {
      // get first element
      Derived * current = list.first();
      // remove first element
      list /= current;

      //execute function
      bool cont = true;
      f(cont,current);
      if(!cont) return cycles;

      // add successors of current;
      successors(list,*current);
    }
    return cycles;
  }

  // overload
  template<typename Derived>
  int Node<Derived>::bfs(std::function<void (bool&,Derived*)> f){
    std::function<void (Set<Derived*> &, const Derived &) > sfunc = [] (Set<Node *>&successors,const Derived &node){        successors |= node.successors();      };
    return bfs(f,sfunc);
  }
NS_END(CORE_NAMESPACE)

