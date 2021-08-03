import SwiftUI
let green = Color(red: 0.729, green: 0.722, blue: 0.424);
let lightGreen = Color(red: 0.729, green: 0.722, blue: 0.424);

struct ContentView: View {
//this is field displays the main view when the user opens the application
    @StateObject var viewModel = FormViewModel()
    var body: some View {
        NavigationView{
            ScrollView{
            VStack{
                
                
                Image("image")
                    .resizable()
                    .aspectRatio(contentMode: .fill)
                    .frame(width: 180, height: 180, alignment: .center)
                    .clipShape(RoundedRectangle(cornerRadius: 70))
                    .padding()
                    .padding()
                    
                HStack{
                Text("Cooking made ").foregroundColor(lightGreen)
                    
                    Text("Simple").bold()
                }
                
                NavigationLink(destination: EmptyView(), label: {})
                NavigationLink(destination: FindRecipe(viewModel: viewModel)//fixes swift UI navigation view bug

                ){

                Text("Find a Recipe").frame(width: 250, height: 50, alignment: .center).background(green).foregroundColor(.white).cornerRadius(8).padding()
                   
                }
                
                NavigationLink(destination: MyRecipes(viewModel : viewModel)){
                
                Text("My CookBook").frame(width: 250, height: 50, alignment: .center).background(lightGreen).foregroundColor(.white).cornerRadius(8)
             
            }
            }.navigationBarTitle("Simply Cooking").padding(20)
      }
    }
  }
}


struct FindRecipe: View {
//this field is where a user will search for a recipe from the database
   
    @StateObject var viewModel = FormViewModel()
    @Environment(\.presentationMode) var presentationMode: Binding<PresentationMode>
   
    var backbutton: some View {
        Button(action: {self.presentationMode.wrappedValue.dismiss()}) {
            HStack {
                
                Text("🍐")
            }
        }
    }

    var body: some View{

        
            VStack{
                
                Form{
                    Section(header : Text("On Hand Ingredients")){
                        
                        TextField("Ingredient One", text: $viewModel.ingredientOne)
                        TextField("Ingredient Two", text: $viewModel.ingredientTwo)
                        TextField("Ingredient Three", text: $viewModel.ingredientThree)
                        TextField("Ingredient Four", text: $viewModel.ingredientFour)
                        TextField("Ingredient Five", text: $viewModel.ingredientFive)
                        TextField("Ingredient Six", text: $viewModel.ingredientSix)
                        TextField("Ingredient Seven", text: $viewModel.ingredientSeven)
                        TextField("Ingredient Eight", text: $viewModel.ingredientEight)
                        TextField("Ingredient Nine", text: $viewModel.ingredientNine)
                        TextField("Ingredient Ten", text: $viewModel.ingredientTen)
                    }
                }
            }
                NavigationLink(destination: FindRecipeNext(viewModel: viewModel)){

                            
                                Text("Next").frame(width: 250, height: 50, alignment: .center).background(green).foregroundColor(.white).cornerRadius(8)
                }
    .navigationBarBackButtonHidden(true)
            .navigationBarItems(leading:backbutton)
        
    }
}
        struct FindRecipeNext: View {
        //this field is where a user will search for a recipe from the database
        
            @StateObject var viewModel = FormViewModel()
            @Environment(\.presentationMode) var presentationMode: Binding<PresentationMode>
           
            var backbutton: some View {
                Button(action: {self.presentationMode.wrappedValue.dismiss()}) {
                    HStack {
                        
                        Text("🍐")
                    }
                }
            }
            
            var body: some View{
                    VStack{
                        
                        Form{
                            Section(header : Text("Allergies")){
                                
                                
                                TextField("Allergy One", text: $viewModel.allergyOne)
                                TextField("Allergy Two", text: $viewModel.allergyTwo)
                                TextField("Allergy Three", text: $viewModel.allergyThree)
                                TextField("Allergy Four", text: $viewModel.allergyFour)
                                TextField("Allergy Five", text: $viewModel.allergyFive)
                                TextField("Allergy Six", text: $viewModel.allergySix)
                                TextField("Allergy Seven", text: $viewModel.allergySeven)
                                TextField("Allergy Eight", text: $viewModel.allergyEight)
                                TextField("Allergy Nine", text: $viewModel.allergyNine)
                                TextField("Allergy Ten", text: $viewModel.allergyTen)
               }
            }
         }
        
                NavigationLink(destination: recipeResults(viewModel: viewModel)){

                    
                    Text("Next").frame(width: 250, height: 50, alignment: .center).background(green).foregroundColor(.white).cornerRadius(8)
                }
        .navigationBarBackButtonHidden(true)
            .navigationBarItems(leading:backbutton)
  }
}
struct recipeResults: View{
    @Environment(\.presentationMode) var presentationMode: Binding<PresentationMode>
    @StateObject var viewModel = FormViewModel()
    @State var matches: String = ""
    @State var test : String = "";
    
    
    
    var backbutton: some View {
        Button(action: {self.presentationMode.wrappedValue.dismiss()}) {
            HStack {
                
                Text("🍐")
                   
            }
        }
    }
    
    
    var body: some View{
        //list of inputted ingredients
        
        //list of inputted ingredients to exclude
        
        
        //this field will display search results to the user preferably in a scrolling navigation list
        VStack{
           //show ingredients so user can confirm and search
            
            Text("Top Picks").font(.largeTitle).bold().padding()
        
               
            Text("Ingredients: " + viewModel.ingredientList).foregroundColor(lightGreen)
            Text("Allergies: " + viewModel.allergyList).foregroundColor(lightGreen)
            
            TextEditor(text: $matches)
                
                .cornerRadius(30)
                .padding()
                .frame(width: 400, height: 560, alignment: .center)
                .cornerRadius(30)
                .overlay(
            RoundedRectangle(cornerRadius: 30).stroke(lightGreen, lineWidth: 2)
            )
        }.navigationBarBackButtonHidden(true)
        .navigationBarItems(leading:backbutton)
        
        Button(action: {
            self.matches = String(cString : getRecipes(viewModel.ingredientInput, viewModel.allergyInput))
             
        }) {
            Text("Confirm & Find")
        }.frame(width: 250, height: 50, alignment: .center).background(green).foregroundColor(.white).cornerRadius(8).frame(maxHeight: .infinity, alignment: .bottom)
        .animation(.spring())
       
    }
}


struct MyRecipes : View {
    @StateObject var viewModel = FormViewModel()
    @Environment(\.presentationMode) var presentationMode: Binding<PresentationMode>
    
    var backbutton: some View {
        Button(action: {self.presentationMode.wrappedValue.dismiss()}) {
            HStack {
                
                Text("🍐")
            
            }
        }
    }

        
        var body: some View{
                          List {
                        
                                NavigationLink(destination: breakfast(viewModel : viewModel)){

                                
                                        Text("Breakfast🧇🥓🥞🍊").frame(width: 250, height: 50, alignment: .center).background(green).foregroundColor(.white).cornerRadius(8)
                            }
                                
                                NavigationLink(destination: lunch(viewModel : viewModel)){

                                
                                        Text("Lunch🥪🍎🍵").frame(width: 250, height: 50, alignment: .center).background(green).foregroundColor(.white).cornerRadius(8)
                            }
                                NavigationLink(destination: lunch(viewModel : viewModel)){

                                
                                        Text("Dinner🍜🫕🥦").frame(width: 250, height: 50, alignment: .center).background(green).foregroundColor(.white).cornerRadius(8)
                            }
                            
                            NavigationLink(destination:snacks(viewModel : viewModel)){

                            
                                    Text("Snacks🥣🍿🧃").frame(width: 250, height: 50, alignment: .center).background(green).foregroundColor(.white).cornerRadius(8)
                        }
                            NavigationLink(destination:holiday(viewModel : viewModel)){

                            
                                    Text("Holidays🎄").frame(width: 250, height: 50, alignment: .center).background(green).foregroundColor(.white).cornerRadius(8)
                        }
                   }
                          
                          .navigationBarTitle(Text("CookBook"))
                    .navigationBarBackButtonHidden(true)
               .navigationBarItems(leading:backbutton)
                            
            .onReceive(NotificationCenter.default.publisher(for: UITableView.selectionDidChangeNotification)) {
                guard let tableView = $0.object as? UITableView,
                      let selectedRow = tableView.indexPathForSelectedRow else { return }
                tableView.deselectRow(at: selectedRow, animated: true)
                
                
                /*https://stackoverflow.com/questions/65411477/swiftui-navigationlink-highlight-staying-highlighted-after-returning-to-previous
                   solution for view selection bug in list view  */
        }
    }

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        
        ContentView().environmentObject(FormViewModel())    }
}

struct breakfast : View {
    @StateObject var viewModel = FormViewModel()    //breakfast cook book page view
    @State var recipes : String = ""
      @Environment(\.presentationMode) var presentationMode: Binding<PresentationMode>
    
    var backbutton: some View {
        
        Button(action: {self.presentationMode.wrappedValue.dismiss()}) {
            HStack {
                
                Text("🍐")
            
            }
        }
    }
    var body: some View{
    VStack{
        
        TextEditor(text: $viewModel.breakfast)
            .cornerRadius(30)
            .padding()
            .frame(width: 400, height: 700, alignment: .center)
            .overlay(
        RoundedRectangle(cornerRadius: 30).stroke(lightGreen, lineWidth: 2)
        )
    }.navigationBarBackButtonHidden(true)
        .navigationBarItems(leading:backbutton)
        .navigationTitle("BreakFast")
        
    }
}

struct lunch : View {
    @StateObject var viewModel = FormViewModel()    //breakfast cook book page view
    @State var recipes : String = ""
      @Environment(\.presentationMode) var presentationMode: Binding<PresentationMode>
    
    var backbutton: some View {
        
        Button(action: {self.presentationMode.wrappedValue.dismiss()}) {
            HStack {
                
                Text("🍐")
            
            }
        }
    }
    var body: some View{
    VStack{
        
        TextEditor(text: $viewModel.lunch)
            .cornerRadius(30)
            .padding()
            .frame(width: 400, height: 700, alignment: .center)
            .overlay(
        RoundedRectangle(cornerRadius: 30).stroke(lightGreen, lineWidth: 2)
        )
    }.navigationBarBackButtonHidden(true)
        .navigationBarItems(leading:backbutton)
        .navigationTitle("Lunch")
        
    }
}

struct dinner : View {
    @StateObject var viewModel = FormViewModel()    //breakfast cook book page view
    @State var recipes : String = ""
      @Environment(\.presentationMode) var presentationMode: Binding<PresentationMode>
    
    var backbutton: some View {
        
        Button(action: {self.presentationMode.wrappedValue.dismiss()}) {
            HStack {
                
                Text("🍐")
            }
        }
    }

    var body: some View{
    VStack{
        
        TextEditor(text: $viewModel.dinner)
            .cornerRadius(30)
            .padding()
            .frame(width: 400, height: 700, alignment: .center)
            .overlay(
        RoundedRectangle(cornerRadius: 30).stroke(lightGreen, lineWidth: 2)
        )
    }.navigationBarBackButtonHidden(true)
        .navigationBarItems(leading:backbutton)
        .navigationTitle("Dinner")
        
    }
}

    struct snacks : View {
        @StateObject var viewModel = FormViewModel()    //breakfast cook book page view
        @State var recipes : String = ""
          @Environment(\.presentationMode) var presentationMode: Binding<PresentationMode>
        
        var backbutton: some View {
            
            Button(action: {self.presentationMode.wrappedValue.dismiss()}) {
                HStack {
                    
                    Text("🍐")
                }
            }
        }

        var body: some View{
        VStack{
            
            TextEditor(text: $viewModel.snacks)
                .cornerRadius(30)
                .padding()
                .frame(width: 400, height: 700, alignment: .center)
                .overlay(
            RoundedRectangle(cornerRadius: 30).stroke(lightGreen, lineWidth: 2)
            )
        }.navigationBarBackButtonHidden(true)
            .navigationBarItems(leading:backbutton)
            .navigationTitle("Snacks")
        }
    }
    
    struct holiday : View {
        @StateObject var viewModel = FormViewModel()    //breakfast cook book page view
        @State var recipes : String = ""
          @Environment(\.presentationMode) var presentationMode: Binding<PresentationMode>
        
        var backbutton: some View {
            
            Button(action: {self.presentationMode.wrappedValue.dismiss()}) {
                HStack {
                    
                    Text("🍐")
                }
            }
        }

        var body: some View{
        VStack{
            
            TextEditor(text: $viewModel.holiday)
                .cornerRadius(30)
                .padding()
                .frame(width: 400, height: 700, alignment: .center)
                .overlay(
            RoundedRectangle(cornerRadius: 30).stroke(lightGreen, lineWidth: 2)
            )
        }.navigationBarBackButtonHidden(true)
            .navigationBarItems(leading:backbutton)
            .navigationTitle("Holidays")
        }
    }
}
    class FormViewModel: ObservableObject{

//variables for the Find Recipe tab
@Published var ingredientOne = "";
@Published var ingredientTwo = "";
@Published var ingredientThree = "";
@Published var ingredientFour = "";
@Published var ingredientFive = "";
@Published var ingredientSix = "";
@Published var ingredientSeven = "";
@Published var ingredientEight = "";
@Published var ingredientNine = "";
@Published var ingredientTen = "";
@Published var allergyOne = "";
@Published var allergyTwo = "";
@Published var allergyThree = "";
@Published var allergyFour = "";
@Published var allergyFive = "";
@Published var allergySix = "";
@Published var allergySeven = "";
@Published var allergyEight = "";
@Published var allergyNine = "";
@Published var allergyTen = "";
//variables for the recipe cook book tabs
@Published var breakfast = "";
@Published var lunch = "";
@Published var dinner = "";
@Published var snacks = "";
@Published var holiday = "";
    
    var allergyInput : String{
        
        var confirmation : String = ""
        let ingredients = [allergyOne, allergyTwo, allergyThree, allergyFour, allergyFive, allergySix, allergySeven, allergyEight, allergyNine, allergyTen]
      
    ingredients.forEach{ allergy in
    
        
        if(allergy != ""){
        confirmation += allergy + ";"
       
      }
    }
        
       
    return String(confirmation.dropLast(1))
  }
    var ingredientInput : String {
        var confirmation : String = ""
    let ingredients = [ingredientOne, ingredientTwo, ingredientThree, ingredientFour, ingredientFive, ingredientSix, ingredientSeven, ingredientEight, ingredientNine, ingredientTen]
      
    ingredients.forEach{ ingredient in
    
        
        if(ingredient != ""){
        confirmation += ingredient + ";"
       
      }
    }
    
   
    return String(confirmation.dropLast(1))
    }
var ingredientList : String{
//this variable prints a list of ingredients on the user confirmation page
        var confirmation : String = ""
    let ingredients = [ingredientOne, ingredientTwo, ingredientThree, ingredientFour, ingredientFive, ingredientSix, ingredientSeven, ingredientEight, ingredientNine, ingredientTen]
      
    ingredients.forEach{ ingredient in
    
        
        if(ingredient != ""){
        confirmation += ingredient + ", "
       
      }
    }
    
    if(confirmation == ""){
        
        return "None"
    }
    return String(confirmation.dropLast(2))
}
    
    
    var allergyList : String{
//this variable prints a list of allergies or excluded ingredients on the user confirmation page
        var confirmation : String = ""
        let ingredients = [allergyOne, allergyTwo, allergyThree, allergyFour, allergyFive, allergySix, allergySeven, allergyEight, allergyNine, allergyTen]
      
    ingredients.forEach{ allergy in
    
        
        if(allergy != ""){
        confirmation += allergy + ", "
       
      }
    }
        
        if(confirmation == ""){
            
            return "None"
        }
    return String(confirmation.dropLast(2))
        
  }
}

