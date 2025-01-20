# Définition des tâches
tasks = [
    {"name": "τ1", "C": 2, "T": 10},
    {"name": "τ2", "C": 2, "T": 10},
    {"name": "τ3", "C": 2, "T": 20},
    {"name": "τ4", "C": 2, "T": 20},
    {"name": "τ5", "C": 2, "T": 40},
    {"name": "τ6", "C": 2, "T": 40},
    {"name": "τ7", "C": 3, "T": 80},
]

# Fonction pour calculer le PGCD de deux nombres
def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

# Fonction pour calculer le PPCM de deux nombres
def lcm_two(a, b):
    return a * b // gcd(a, b)

# Fonction pour calculer le PPCM d'une liste de nombres
def lcm(numbers):
    result = numbers[0]
    for number in numbers[1:]:
        result = lcm_two(result, number)
    return result

# Vérification de la faisabilité avec EDF
def check_schedulability(tasks):
    print("=== Vérification de la faisabilité ===")
    utilization = sum(task["C"] / task["T"] for task in tasks)
    for task in tasks:
        print(f"Tâche {task['name']} : C = {task['C']}, T = {task['T']}, Utilisation = {task['C'] / task['T']:.2f}")
    print(f"Utilisation totale U = {utilization:.2f}")
    return utilization <= 1, utilization

# Simulation d'ordonnancement EDF
def edf_schedule(tasks):
    print("\n=== Début de la simulation EDF ===")
    # Calcul de l'hyper-période
    periods = [task["T"] for task in tasks]
    hyper_period = lcm(periods)
    print(f"Hyper-période calculée : {hyper_period} unités de temps")

    # Initialisation des tâches
    print("\nInitialisation des tâches...")
    for task in tasks:
        task["remaining_time"] = 0
        task["next_deadline"] = task["T"]
        print(f"Tâche {task['name']} : C = {task['C']}, T = {task['T']}, Prochaine deadline = {task['next_deadline']}")

    timeline = []  # Planning des tâches

    # Simulation sur l'hyper-période
    for time in range(hyper_period):
        print(f"\n--- Temps {time} ---")

        # Libérer les jobs à leurs périodes respectives
        for task in tasks:
            if time % task["T"] == 0:
                task["remaining_time"] = task["C"]
                task["next_deadline"] = time + task["T"]
                print(f"Tâche {task['name']} : Nouveau job libéré (Remaining Time = {task['remaining_time']}, Deadline = {task['next_deadline']})")

        # Sélectionner les tâches éligibles
        eligible_tasks = [task for task in tasks if task["remaining_time"] > 0]
        if eligible_tasks:
            # Trier par échéance (deadline)
            eligible_tasks.sort(key=lambda t: t["next_deadline"])
            current_task = eligible_tasks[0]
            current_task["remaining_time"] -= 1
            print(f"Tâche sélectionnée : {current_task['name']} (Remaining Time après exécution = {current_task['remaining_time']})")
            timeline.append((time, current_task["name"]))
        else:
            print("Aucune tâche éligible, CPU inactif.")
            timeline.append((time, "Idle"))

    return timeline

# Vérification et génération du planning
schedulable, utilization = check_schedulability(tasks)

if schedulable:
    print("\nTâches ordonnançables avec EDF.")
    schedule = edf_schedule(tasks)
    print("\n=== Planning EDF généré ===")
    for time, task in schedule:
        print(f"Time {time}: {task}")
else:
    print("\nTâches non ordonnançables avec EDF.")
